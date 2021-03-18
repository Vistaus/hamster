/*
 * Copyright (c) 2021 Slawek Tuleja
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "WindowBody.h"

WindowBody::WindowBody()
    : item_list(1, false, Gtk::SELECTION_MULTIPLE), // Where '1' means: show one column only (column name: 'item_display_value')
      selection_order {SelectionOrder::SHIFT_DOWN},
      store_type {StoreType::PRIMARY}
{
    ref_clipboard = Gtk::Clipboard::get();
    ref_clipboard->signal_owner_change().connect(sigc::mem_fun(*this, &WindowBody::on_clipboard_change));

    ref_settings = Gio::Settings::create("com.github.slawtul.hamster");

    search_entry.signal_search_changed().connect(sigc::mem_fun(*this, &WindowBody::on_search_change));
    search_entry.signal_event().connect(sigc::mem_fun(*this, &WindowBody::on_search_entry_event));
    search_entry.set_margin_top(4);
    search_entry.set_margin_right(4);
    search_entry.set_margin_bottom(4);
    search_entry.set_margin_left(4);

    pack_start(search_entry);
    pack_start(separator);
    pack_start(scrolled_win);

    scrolled_win.set_size_request(-1, 640);
    scrolled_win.add(item_list);

    ref_primary_item_store = Gtk::ListStore::create(columns);
    ref_secondary_item_store = Gtk::ListStore::create(columns);

    item_list.set_model(ref_primary_item_store);
    item_list.set_headers_visible(false);
    item_list.set_enable_search(false);
    item_list.set_search_entry(search_entry);
    item_list.signal_event().connect(sigc::mem_fun(*this, &WindowBody::on_item_list_event));
    item_list.signal_key_press_event().connect(sigc::mem_fun(*this, &WindowBody::on_item_list_key_press));

    const auto row0 = *(ref_primary_item_store->append());
    row0[columns.item_value] = _("Welcome to Hamster !");
    row0[columns.item_display_value] = _("Welcome to Hamster !");

    const auto row1 = *(ref_primary_item_store->append());
    row1[columns.item_value] = _("Press <Alt+S> to open shortcuts window");
    row1[columns.item_display_value] = _("Press <Alt+S> to open shortcuts window");

    const auto row2 = *(ref_primary_item_store->append());
    row2[columns.item_value] = _("Press <Alt+P> to open preferences window");
    row2[columns.item_display_value] = _("Press <Alt+P> to open preferences window");
}

void WindowBody::on_search_change()
{
    ref_secondary_item_store->clear();
    store_type = StoreType::PRIMARY;
    if (search_entry.get_text().length() >= 2)
    {
        TextUtil tu {};
        auto search_str = (std::string) search_entry.get_text();

        // Escape non-alpha chars because we want treat them as regular chars
        // Eg. user wants to use '.' as dot not as 'any' regexp char
        // Eg. user wants to use '*' as star not as 'zero or more' regexp character, etc...
        auto esc_str = tu.escape_nonalpha(search_str);
        const auto pattern = std::regex {esc_str, std::regex_constants::icase};
        std::smatch sm {};

        for (const auto& row : ref_primary_item_store->children())
        {
            if (std::regex_search(row.get_value(columns.item_value).raw(), sm, pattern))
            {
                const auto s_row = *(ref_secondary_item_store->append());
                s_row[columns.item_value] = row.get_value(columns.item_value);
                s_row[columns.item_display_value] = row.get_value(columns.item_display_value);
            }
        }
        item_list.set_model(ref_secondary_item_store);
        store_type = StoreType::SECONDARY;
    }
    else
    {
        store_type = StoreType::PRIMARY;
        item_list.set_model(ref_primary_item_store);
    }
}

void WindowBody::on_clipboard_change(GdkEventOwnerChange* event)
{
    if (event == nullptr)
    {
        return;
    }

    // Waiting for new copied text...
    auto text = ref_clipboard->wait_for_text();

    TextUtil tu {};
    if (tu.has_only_spaces(text))
    {
        return;
    }

    if (ref_settings->get_boolean("eliminate-spaces"))
    {
        text = tu.trim_str(text);
    }

    // Delete just copied text if already exits in item list... (does not allow to have duplicated items in the list)
    delete_items(ref_primary_item_store->children(), text);

    const auto row = *(ref_primary_item_store->prepend());
    row[columns.item_value] = text;                                     // Save in memory original text value
    row[columns.item_display_value] = tu.calculate_display_value(text); // Show short, one liner text value

    item_list.set_cursor(ref_primary_item_store->get_path(row));
    item_list.scroll_to_row(ref_primary_item_store->get_path(row));

    // Delete if too many...
    delete_last_items((int) ref_primary_item_store->children().size(), (int) ref_settings->get_double("item-list-size"));

    g_print("stored items: %d\n", ref_primary_item_store->children().size());
}

bool WindowBody::on_item_list_event(GdkEvent* gdk_event)
{
    // Events with 'Enter' key cannot be fetched with 'signal_key_press_event' in ListTextView widget
    // In this widget 'Enter' means: row edit mode
    if (gdk_event == nullptr)
    {
        return false;
    }

    const auto SHIFT_MASK = 17; // On modern PC

    // 'SHIFT + ENTER' paste but before show prefix and suffix entry fields
    if ((gdk_event->key.state == SHIFT_MASK || gdk_event->key.state == GDK_SHIFT_MASK) &&
        gdk_event->type == GDK_KEY_PRESS && gdk_event->key.keyval == GDK_KEY_Return)
    {
        g_print("Shift + Enter keys pressed\n");
        return true;
    }

    // 'ENTER' paste
    if (gdk_event->type == GDK_KEY_PRESS && gdk_event->key.keyval == GDK_KEY_Return)
    {
        search_entry.grab_focus();
        this->get_window()->iconify();

        auto prefix = (std::string) ref_settings->get_string("item-prefix");
        auto suffix = (std::string) ref_settings->get_string("item-suffix");

        TextUtil tu {};
        prefix = tu.convert_to_newline_or_tab(prefix);
        suffix = tu.convert_to_newline_or_tab(suffix);

        const auto path_list = get_selected_paths();
        auto selected_paths = path_list; // Reverse a copied vector

        if (selection_order == SelectionOrder::SHIFT_UP)
        {
            std::reverse(selected_paths.begin(), selected_paths.end());
        }

        Glib::ustring text_to_paste = "";
        for (const auto& path : selected_paths)
        {
            const auto row = get_row(path);
            const auto item_value = row.get_value(columns.item_value);
            text_to_paste += path_list.size() == 1 ? item_value : prefix + item_value + suffix;
        }

        ref_clipboard->set_text(text_to_paste); // Send text to clipboard...

        std::this_thread::sleep_for(std::chrono::milliseconds((short) ref_settings->get_double("delay-pasting")));
        send_ctrl_v_key_event();

        return true;
    }

    // ROWS SELECTION HANDLING
    if (get_selected_paths().size() == 1)
    {
        selection_order = SelectionOrder::SHIFT_DOWN;
    }

    // 'SHIFT + UP' select up
    if ((gdk_event->key.state == SHIFT_MASK || gdk_event->key.state == GDK_SHIFT_MASK) &&
        gdk_event->type == GDK_KEY_PRESS && gdk_event->key.keyval == GDK_KEY_Up)
    {
        selection_order = SelectionOrder::SHIFT_UP;
    }

    // 'SHIFT + DOWN' select down
    if ((gdk_event->key.state == SHIFT_MASK || gdk_event->key.state == GDK_SHIFT_MASK) &&
        gdk_event->type == GDK_KEY_PRESS && gdk_event->key.keyval == GDK_KEY_Down)
    {
        selection_order = SelectionOrder::SHIFT_DOWN;
    }

    return false;
}

bool WindowBody::on_item_list_key_press(GdkEventKey* key_event)
{
    if (key_event == nullptr)
    {
        return false;
    }

    // 'ESCAPE' OR 'TAB' KEY PRESSED
    if (key_event->keyval == GDK_KEY_Escape || key_event->keyval == GDK_KEY_Tab || key_event->keyval == GDK_KEY_slash)
    {
        search_entry.grab_focus();
        return true;
    }

    const auto ALT_MASK = 24; // On modern PC

    // 'ALT + D' show item details window
    if ((key_event->state == ALT_MASK || key_event->state == GDK_MOD1_MASK) && key_event->keyval == GDK_KEY_d)
    {
        show_item_details_window(get_row(get_selected_paths()[0]).get_value(columns.item_value));
        return true;
    }

    // 'ALT + L' transform to lowercase
    if ((key_event->state == ALT_MASK || key_event->state == GDK_MOD1_MASK) && key_event->keyval == GDK_KEY_l)
    {
        if (store_type == StoreType::SECONDARY)
        {
            transform_to_lowercase(find_primary_store_rows(get_selected_paths())); // secondary store selected paths
        }
        transform_to_lowercase(get_selected_paths());
        return true;
    }

    // 'ALT + U' transform to uppercase
    if ((key_event->state == ALT_MASK || key_event->state == GDK_MOD1_MASK) && key_event->keyval == GDK_KEY_u)
    {
        if (store_type == StoreType::SECONDARY)
        {
            transform_to_uppercase(find_primary_store_rows(get_selected_paths())); // secondary store selected paths
        }
        transform_to_uppercase(get_selected_paths());
        return true;
    }

    // 'DELETE' item
    if (key_event->keyval == GDK_KEY_Delete)
    {
        if (store_type == StoreType::SECONDARY)
        {
            delete_items(find_primary_store_rows(get_selected_paths())); // secondary store selected paths
        }
        delete_items(get_selected_paths());
        return true;
    }

    return false;
}

void WindowBody::delete_items(std::vector<Gtk::TreePath>&& paths)
{
    for (const auto& path : paths)
    {
        Glib::RefPtr<Gtk::ListStore>::cast_dynamic(item_list.get_model())->erase(get_row(path));
    }
}

void WindowBody::delete_items(std::vector<Gtk::TreeRow>&& rows) const
{
    for (const auto& row : rows)
    {
        ref_primary_item_store->erase(row);
    }
}

void WindowBody::delete_items(Gtk::TreeNodeChildren&& rows, const Glib::ustring& text) const
{
    for (const auto& row : rows)
    {
        if (text.length() == row.get_value(columns.item_value).length() && text == row.get_value(columns.item_value))
        {
            ref_primary_item_store->erase(row);
        }
    }
}

void WindowBody::delete_last_items(int store_sz, int max_list_size) const
{
    const auto diff_sz = store_sz - max_list_size;
    if (diff_sz > 0)
    {
        for (int i = 1; i <= diff_sz; ++i)
        {
            ref_primary_item_store->erase(ref_primary_item_store->children()[store_sz - i]);
        }
    }
}

void WindowBody::transform_to_lowercase(std::vector<Gtk::TreePath>&& paths)
{
    for (const auto& path : paths)
    {
        const auto row = get_row(path);
        row[columns.item_display_value] = row.get_value(columns.item_display_value).lowercase();
        row[columns.item_value] = row.get_value(columns.item_value).lowercase();
    }
}

void WindowBody::transform_to_lowercase(std::vector<Gtk::TreeRow>&& rows) const
{
    for (const auto& row : rows)
    {
        row[columns.item_display_value] = row.get_value(columns.item_display_value).lowercase();
        row[columns.item_value] = row.get_value(columns.item_value).lowercase();
    }
}

void WindowBody::transform_to_uppercase(std::vector<Gtk::TreePath>&& paths)
{
    for (const auto& path : paths)
    {
        const auto row = get_row(path);
        row[columns.item_display_value] = row.get_value(columns.item_display_value).uppercase();
        row[columns.item_value] = row.get_value(columns.item_value).uppercase();
    }
}

void WindowBody::transform_to_uppercase(std::vector<Gtk::TreeRow>&& rows) const
{
    for (const auto& row : rows)
    {
        row[columns.item_display_value] = row.get_value(columns.item_display_value).uppercase();
        row[columns.item_value] = row.get_value(columns.item_value).uppercase();
    }
}

bool WindowBody::on_search_entry_event(GdkEvent* gdk_event)
{
    if (gdk_event == nullptr)
    {
        return false;
    }

    // 'DOWN' move to list
    if (gdk_event->type == GDK_KEY_PRESS && gdk_event->key.keyval == GDK_KEY_Down)
    {
        item_list.grab_focus();
        return true;
    }

    // 'ESC' clear search entry or minimize application
    if (gdk_event->type == GDK_KEY_PRESS && gdk_event->key.keyval == GDK_KEY_Escape)
    {
        search_entry.get_text_length() == 0 ? this->get_window()->iconify() : search_entry.set_text("");
        search_entry.grab_focus();
        return true;
    }

    return false;
}

void WindowBody::send_ctrl_v_key_event()
{
    const auto display = XOpenDisplay(nullptr);
    const auto left_control_key = XKeysymToKeycode(display, XK_Control_L);
    const auto v_key = XKeysymToKeycode(display, XK_v);

    XTestGrabControl(display, True);
    XTestFakeKeyEvent(display, left_control_key, True, 0);
    XTestFakeKeyEvent(display, v_key, True, 0);  // True means key press
    XTestFakeKeyEvent(display, v_key, False, 0); // False means key release
    XTestFakeKeyEvent(display, left_control_key, False, 0);

    XSync(display, False);
    XTestGrabControl(display, False);
}

void WindowBody::show_item_details_window(const Glib::ustring& text)
{
    item_details_window.set_text(text);
    item_details_window.show_all();
    item_details_window.present();
}

// HELPER METHODS
std::vector<Gtk::TreeModel::Path> WindowBody::get_selected_paths()
{
    return item_list.get_selection()->get_selected_rows();
}

Gtk::TreeRow WindowBody::get_row(const Gtk::TreeModel::Path& path)
{
    return *(item_list.get_model()->get_iter(path));
}

std::vector<Gtk::TreeRow> WindowBody::find_primary_store_rows(std::vector<Gtk::TreePath>&& secondary_store_paths)
{
    std::vector<Gtk::TreeRow> rows_to_update {};
    rows_to_update.reserve(secondary_store_paths.size());

    for (const auto& path : secondary_store_paths)
    {
        const auto s_row = get_row(path);
        for (const auto& row : ref_primary_item_store->children())
        {
            const auto s_rv = s_row.get_value(columns.item_value);
            const auto rv = row.get_value(columns.item_value);
            if (s_rv.length() == rv.length() && s_rv == rv)
            {
                rows_to_update.emplace_back(row);
                break;
            }
        }
    }
    return rows_to_update;
}
