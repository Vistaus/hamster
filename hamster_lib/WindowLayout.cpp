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

#include "WindowLayout.h"

WindowLayout::WindowLayout() : item_list(1, false, Gtk::SELECTION_MULTIPLE)
{
    search_entry.signal_search_changed().connect(sigc::mem_fun(*this, &WindowLayout::on_search_change));
    search_entry.set_margin_top(6);
    search_entry.set_margin_right(6);
    search_entry.set_margin_bottom(6);
    search_entry.set_margin_left(6);

    pack_start(search_entry);
    pack_start(separator);
    pack_start(scrolled_win);

    scrolled_win.set_size_request(-1, 640);
    scrolled_win.add(item_list);

    item_list.set_headers_visible(false);
    item_list.set_enable_search(false);
}

void WindowLayout::on_search_change()
{
    g_print("%s\n", search_entry.get_text().c_str());
}
