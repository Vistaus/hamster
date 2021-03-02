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
    item_list.set_model(ref_item_store);
    item_list.set_headers_visible(false);
    item_list.set_enable_search(false);
    item_list.set_search_entry(search_entry);
    item_list.signal_event().connect(sigc::mem_fun(*this, &WindowBody::on_item_list_event));
    item_list.signal_key_press_event().connect(sigc::mem_fun(*this, &WindowBody::on_item_list_key_press));

    const auto row1 = *(ref_item_store->prepend());
    row1[columns.item_value] = "hamster";
    row1[columns.item_display_value] = "hamster";

    const auto row2 = *(ref_item_store->prepend());
    row2[columns.item_value] = "clipboard manager";
    row2[columns.item_display_value] = "clipboard manager";

    const auto row3 = *(ref_item_store->prepend());
    row3[columns.item_value] = "elementary os";
    row3[columns.item_display_value] = "elementary os";

    const auto row4 = *(ref_item_store->prepend());
    row4[columns.item_value] = "linux";
    row4[columns.item_display_value] = "linux";
}

void WindowBody::on_search_change()
{
    g_print("%s\n", search_entry.get_text().c_str());
}

void WindowBody::on_clipboard_change(GdkEventOwnerChange *event) const
{
    if (event == nullptr)
    {
        return;
    }

    if (auto text = ref_clipboard->wait_for_text(); !TextUtil::has_only_spaces(text))
    {
        const auto row = *(ref_item_store->prepend());
        row[columns.item_value] = text; // Save in memory original text value

        text = TextUtil::join_lines(text, 48);
        text = TextUtil::trim_str(text);
        text = TextUtil::sub_str(text, 40, "...");
        row[columns.item_display_value] = text; // Show short one liner text value

        g_print("display value length: %lu\n", text.length());
    }
    g_print("item store size: %d\n", ref_item_store->children().size());
}

bool WindowBody::on_item_list_event(GdkEvent *gdk_event)
{
    if (gdk_event == nullptr)
    {
        return false;
    }

    // Events with 'Enter' key cannot be fetched with 'signal_key_press_event' in ListTextView widget
    // In this widget 'Enter' means: row edit mode

    // 'SHIFT + ENTER' KEYS PRESSED
    const auto SHIFT_MASK = 17; // On modern PC
    if ((gdk_event->key.state == SHIFT_MASK || gdk_event->key.state == GDK_SHIFT_MASK) &&
        gdk_event->type == GDK_KEY_PRESS &&
        gdk_event->key.keyval == GDK_KEY_Return)
    {
        g_print("Shift + Enter keys pressed\n");
        return true;
    }

    // 'ENTER' KEY PRESSED
    if (gdk_event->type == GDK_KEY_PRESS && gdk_event->key.keyval == GDK_KEY_Return)
    {
        g_print("Enter pressed\n");

        this->get_window()->iconify();
        ref_clipboard->set_text("New text item in clipboard...");

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        Display *disp = XOpenDisplay(nullptr);
        KeyCode keycode, modcode;
        KeySym keysym = XK_v;
        KeySym modsym = XK_Control_L;
        keycode = XKeysymToKeycode(disp, keysym);
        XTestGrabControl(disp, True);

        modcode = XKeysymToKeycode(disp, modsym);

        /* Generate modkey press */
        XTestFakeKeyEvent(disp, modcode, True, 0);

        /* Generate regular key press and release */
        XTestFakeKeyEvent(disp, keycode, True, 0);
        XTestFakeKeyEvent(disp, keycode, False, 0);

        /* Generate modkey release */
        XTestFakeKeyEvent(disp, modcode, False, 0);

        XSync(disp, False);
        XTestGrabControl(disp, False);


//        system("/home/slawtul/repos/hamster/data/fakeKey");
        // auto ref_display = Gdk::Display::get_default();
        // auto ref_screen = Gdk::Screen::get_default();
        // auto all_opened_windows = ref_screen->get_window_stack();
        // for (const auto &open_window : all_opened_windows) {
        //     open_window->maximize();
        // }
//
//        GdkEvent *event_key = gdk_event_new(GDK_KEY_PRESS);
//        //((GdkEventKey *) event_key)->window = this->get_window()->gobj();
//        ((GdkEventKey *) event_key)->window = ref_display->get_default_group()->gobj();
//        ((GdkEventKey *) event_key)->send_event = TRUE;
//        ((GdkEventKey *) event_key)->time = GDK_CURRENT_TIME;
//        ((GdkEventKey *) event_key)->state = 20;
//        ((GdkEventKey *) event_key)->keyval = GDK_KEY_v;
//        ((GdkEventKey *) event_key)->hardware_keycode = 55;
//        ((GdkEventKey *) event_key)->group = 0;
//
//        Gdk::Event(event_key).put();New text item in clipboard...



        return true;
    }
    return false;
}

bool WindowBody::on_item_list_key_press(GdkEventKey *key_event)
{
    if (key_event == nullptr)
    {
        return false;
    }

    const auto &ref_selection = item_list.get_selection();

    // 'ESCAPE' OR 'TAB' KEY PRESSED
    if (key_event->keyval == GDK_KEY_Escape || key_event->keyval == GDK_KEY_Tab)
    {
        search_entry.grab_focus();
        return true;
    }

    // 'ALT + L' KEYS PRESSED
    const auto ALT_MASK = 24; // On modern PC
    if ((key_event->state == ALT_MASK || key_event->state == GDK_MOD1_MASK) && key_event->keyval == GDK_KEY_l)
    {
        for ([[maybe_unused]] const auto &_ : item_list.get_selected())
        {
            ref_selection->selected_foreach_iter(
                sigc::mem_fun(*this, &WindowBody::selected_row_change_letter_case_callback));
        }
        return true;
    }

    // 'DELETE' KEY PRESSED
    if (key_event->keyval == GDK_KEY_Delete)
    {
        for ([[maybe_unused]] const auto &_ : item_list.get_selected())
        {
            ref_selection->selected_foreach_iter(sigc::mem_fun(*this, &WindowBody::selected_row_delete_callback));
        }
        return true;
    }

    return false;
}

void WindowBody::selected_row_delete_callback(const Gtk::TreeModel::iterator &iter) const
{
    ref_item_store->erase(iter);
}

bool WindowBody::on_search_entry_event(GdkEvent *gdk_event)
{
    if (gdk_event == nullptr)
    {
        return false;
    }

    if (gdk_event->type == GDK_KEY_PRESS && gdk_event->key.keyval == GDK_KEY_Down)
    {
        item_list.grab_focus();
        return true;
    }
    return false;
}

void WindowBody::selected_row_change_letter_case_callback(const Gtk::TreeModel::iterator &iter) const
{
    auto row = *(iter);
    auto item_value = row.get_value(columns.item_display_value);
    row[columns.item_display_value] = item_value.uppercase();
}
