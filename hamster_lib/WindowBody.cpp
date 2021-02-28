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
#include "util/text/TextUtil.h"

WindowBody::WindowBody()
    : item_list(1, false, Gtk::SELECTION_MULTIPLE) // Where '1' means: show 'item_display_value' column only!
{
    ref_clipboard = Gtk::Clipboard::get();
    ref_clipboard->signal_owner_change().connect(sigc::mem_fun(*this, &WindowBody::on_clipboard_change));

    search_entry.signal_search_changed().connect(sigc::mem_fun(*this, &WindowBody::on_search_change));
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
    item_list.signal_key_press_event().connect(sigc::mem_fun(*this, &WindowBody::on_key_press));

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

bool WindowBody::on_key_press(GdkEventKey *key_event)
{
    if (key_event == nullptr)
    {
        return Widget::on_key_press_event(key_event);
    }

    // 'DELETE' KEY PRESSED
    if (const auto &ref_selection = item_list.get_selection();
        key_event->keyval == GDK_KEY_Delete)
    {
        for (auto const _ : item_list.get_selected())
        {
            ref_selection->selected_foreach_iter(sigc::mem_fun(*this, &WindowBody::selected_row_delete_callback));
        }
        return true;
    }

    return Widget::on_key_press_event(key_event);
}

void WindowBody::selected_row_delete_callback(const Gtk::TreeModel::iterator &iter) const
{
    ref_item_store->erase(iter);
}
