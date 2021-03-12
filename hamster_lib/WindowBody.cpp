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
    : item_list(1, false, Gtk::SELECTION_MULTIPLE) // Where '1' means: show 'item_display_value' column only!
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

    ref_item_store = Gtk::ListStore::create(columns);
    ref_searched_item_store = Gtk::ListStore::create(columns);

    item_list.set_model(ref_item_store);
    item_list.set_headers_visible(false);
    item_list.set_enable_search(false);
    item_list.set_search_entry(search_entry);
    item_list.signal_event().connect(sigc::mem_fun(*this, &WindowBody::on_item_list_event));
    item_list.signal_key_press_event().connect(sigc::mem_fun(*this, &WindowBody::on_item_list_key_press));

    const auto row0 = *(ref_item_store->append());
    row0[columns.item_value] = _("Welcome to Hamster !");
    row0[columns.item_display_value] = _("Welcome to Hamster !");

    const auto row1 = *(ref_item_store->append());
    row1[columns.item_value] = _("Press <Alt+S> to open shortcuts window");
    row1[columns.item_display_value] = _("Press <Alt+S> to open shortcuts window");

    const auto row2 = *(ref_item_store->append());
    row2[columns.item_value] = _("Press <Alt+P> to open preferences window");
    row2[columns.item_display_value] = _("Press <Alt+P> to open preferences window");
}

void WindowBody::on_search_change()
{
    ref_searched_item_store->clear();
    if (search_entry.get_text().length() >= 2)
    {
        TextUtil tu {};
        auto search_str = (std::string) search_entry.get_text();

        // Escape nonaplha chars because we want treat them as regular chars
        // Eg. user wants to use '.' as dot not as 'any' regexp char
        // Eg. user wants to use '*' as star not as 'zero or more' regexp character, etc...
        auto esc_str = tu.escape_nonalpha(search_str);
        const auto pattern = std::regex {esc_str, std::regex_constants::icase};
        std::smatch sm {};

        // TODO: For huge text item list below regex search should be done with separate threads
        for (const auto& row : ref_item_store->children())
        {
            if (std::regex_search(row.get_value(columns.item_value).raw(), sm, pattern))
            {
                const auto s_row = *(ref_searched_item_store->append());
                s_row[columns.item_value] = row.get_value(columns.item_value);
                s_row[columns.item_display_value] = row.get_value(columns.item_display_value);
            }
        }
        item_list.set_model(ref_searched_item_store);
    }
    else
    {
        item_list.set_model(ref_item_store);
    }
}

void WindowBody::on_clipboard_change(GdkEventOwnerChange* event)
{
    if (event == nullptr)
    {
        return;
    }

    auto text = ref_clipboard->wait_for_text();

    TextUtil tu {};
    if (tu.has_only_spaces(text))
    {
        return;
    }

    const auto eliminate_space = ref_settings->get_boolean("eliminate-spaces");
    if (eliminate_space)
    {
        text = tu.trim_str(text);
    }

    // Delete just copied text if already exits in item list...
    for (const auto& row : ref_item_store->children())
    {
        if (text.length() == row.get_value(columns.item_value).length() && text == row.get_value(columns.item_value))
        {
            ref_item_store->erase(row);
        }
    }

    const auto row = *(ref_item_store->prepend());
    row[columns.item_value] = text; // Save in memory original text value

    text = tu.join_lines(text, 48);
    text = tu.trim_str(text);
    text = tu.sub_str(text, 40, "...");
    row[columns.item_display_value] = text; // Show short, one liner text value

    item_list.set_cursor(ref_item_store->get_path(row));
    item_list.scroll_to_row(ref_item_store->get_path(row));


    // Delete last text items if too many in the list...
    const auto list_size_setting = (int) ref_settings->get_double("item-list-size");
    auto item_store_sz = (int) ref_item_store->children().size();
    auto diff_sz = item_store_sz - list_size_setting;
    if (diff_sz > 0)
    {
        for (int i = 1; i <= diff_sz; ++i)
        {
            ref_item_store->erase(ref_item_store->children()[item_store_sz - i]);
        }
    }
    g_print("stored items: %d\n", ref_item_store->children().size());
}

bool WindowBody::on_item_list_event(GdkEvent* gdk_event)
{
    if (gdk_event == nullptr)
    {
        return false;
    }

    const auto ref_selection = item_list.get_selection();

    // Events with 'Enter' key cannot be fetched with 'signal_key_press_event' in ListTextView widget
    // In this widget 'Enter' means: row edit mode

    const auto SHIFT_MASK = 17; // On modern PC

    // 'SHIFT + ENTER' KEYS PRESSED
    if ((gdk_event->key.state == SHIFT_MASK || gdk_event->key.state == GDK_SHIFT_MASK) &&
        gdk_event->type == GDK_KEY_PRESS && gdk_event->key.keyval == GDK_KEY_Return)
    {
        g_print("Shift + Enter keys pressed\n");
        return true;
    }

    // 'ENTER' KEY PRESSED
    if (gdk_event->type == GDK_KEY_PRESS && gdk_event->key.keyval == GDK_KEY_Return)
    {
        search_entry.grab_focus();
        this->get_window()->iconify();

        const auto path_list = item_list.get_selection()->get_selected_rows();
        const auto paths_sz = path_list.size();

        auto prefix = (std::string) ref_settings->get_string("item-prefix");
        auto suffix = (std::string) ref_settings->get_string("item-suffix");

        TextUtil tu {};
        prefix = tu.convert_to_newline_or_tab(prefix);
        suffix = tu.convert_to_newline_or_tab(suffix);

        Glib::ustring text_to_paste = "";
        for (const auto& path : path_list)
        {
            const auto row = *(ref_item_store->get_iter(path));
            const auto item_value = row.get_value(columns.item_value);
            text_to_paste += paths_sz == 1 ? item_value : prefix + item_value + suffix;
        }

        ref_clipboard->set_text(text_to_paste);

        const auto delay_pasting = (short) ref_settings->get_double("delay-pasting");
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_pasting));
        send_ctrl_v_key_event();

        return true;
    }
    return false;
}

bool WindowBody::on_item_list_key_press(GdkEventKey* key_event)
{
    if (key_event == nullptr)
    {
        return false;
    }

    const auto& ref_selection = item_list.get_selection();

    // 'ESCAPE' OR 'TAB' KEY PRESSED
    if (key_event->keyval == GDK_KEY_Escape || key_event->keyval == GDK_KEY_Tab || key_event->keyval == GDK_KEY_slash)
    {
        search_entry.grab_focus();
        return true;
    }

    const auto ALT_MASK = 24; // On modern PC

    // 'ALT + L' KEYS PRESSED (transform to lowercase)
    if ((key_event->state == ALT_MASK || key_event->state == GDK_MOD1_MASK) && key_event->keyval == GDK_KEY_l)
    {
        for (const auto& path : item_list.get_selection()->get_selected_rows())
        {
            const auto row = *(ref_item_store->get_iter(path));
            const auto item_disp_value = row.get_value(columns.item_display_value);
            const auto item_value = row.get_value(columns.item_value);
            row[columns.item_display_value] = item_disp_value.lowercase();
            row[columns.item_value] = item_value.lowercase();
        }
        return true;
    }

    // 'ALT + U' KEYS PRESSED (transform to uppercase)
    if ((key_event->state == ALT_MASK || key_event->state == GDK_MOD1_MASK) && key_event->keyval == GDK_KEY_u)
    {
        for (const auto& path : item_list.get_selection()->get_selected_rows())
        {
            const auto row = *(ref_item_store->get_iter(path));
            const auto item_disp_value = row.get_value(columns.item_display_value);
            const auto item_value = row.get_value(columns.item_value);
            row[columns.item_display_value] = item_disp_value.uppercase();
            row[columns.item_value] = item_value.uppercase();
        }
        return true;
    }

    // 'DELETE' KEY PRESSED
    if (key_event->keyval == GDK_KEY_Delete)
    {
        for (const auto& path : item_list.get_selection()->get_selected_rows())
        {
            const auto row = *(ref_item_store->get_iter(path));
            ref_item_store->erase(row);
        }
        return true;
    }

    return false;
}

bool WindowBody::on_search_entry_event(GdkEvent* gdk_event)
{
    if (gdk_event == nullptr)
    {
        return false;
    }

    // 'DOWN' KEY PRESSED (move to list)
    if (gdk_event->type == GDK_KEY_PRESS && gdk_event->key.keyval == GDK_KEY_Down)
    {
        item_list.grab_focus();
        return true;
    }

    // 'ESC' KEY PRESSED (clear search entry or minimize application)
    if (gdk_event->type == GDK_KEY_PRESS && gdk_event->key.keyval == GDK_KEY_Escape)
    {
        search_entry.get_text_length() == 0 ? this->get_window()->iconify() : search_entry.set_text("");
        search_entry.grab_focus();
        return true;
    }

    return false;
}

void WindowBody::send_ctrl_v_key_event() const
{
    const auto disp = XOpenDisplay(nullptr);
    const auto left_control_key = XKeysymToKeycode(disp, XK_Control_L);
    const auto v_key = XKeysymToKeycode(disp, XK_v);

    XTestGrabControl(disp, True);
    XTestFakeKeyEvent(disp, left_control_key, True, 0);
    XTestFakeKeyEvent(disp, v_key, True, 0);  // True means key press
    XTestFakeKeyEvent(disp, v_key, False, 0); // False means key release
    XTestFakeKeyEvent(disp, left_control_key, False, 0);

    XSync(disp, False);
    XTestGrabControl(disp, False);
}
