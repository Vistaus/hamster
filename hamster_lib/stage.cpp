/*
 * Copyright (c) 2021 Slawek Tuleja
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Slawek Tuleja <slawek.tuleja@gmail.com>
 */

#include "stage.h"

Stage::Stage()
    : search_entry(),
      scrolled_window(),
      list_view_text(1, false, Gtk::SELECTION_MULTIPLE),
      button("OK")
{
    set_orientation(Gtk::ORIENTATION_VERTICAL);

    search_entry.signal_search_changed().connect(sigc::mem_fun(*this, &Stage::on_search_change));

    pack_start(search_entry);
    pack_start(scrolled_window);
    pack_start(button);

    button.signal_clicked().connect(sigc::mem_fun(*this, &Stage::on_items_select));

    scrolled_window.set_size_request(-1, 640);
    scrolled_window.add(list_view_text);

    list_view_text.set_column_title(0, "Items");
    list_view_text.set_enable_search(false);

    list_view_text.prepend("...");
    list_view_text.prepend("...");
    list_view_text.prepend("...");
    list_view_text.prepend("...");
    list_view_text.prepend("...");
    list_view_text.prepend("...");
    list_view_text.prepend("...");
    list_view_text.prepend("...");
    list_view_text.prepend("...");
    list_view_text.prepend("...");
    list_view_text.prepend("...");
    list_view_text.prepend("...");
    list_view_text.prepend("...");
    list_view_text.prepend("...");
    list_view_text.prepend("...");
    list_view_text.prepend("...");
    list_view_text.prepend("...");
    list_view_text.prepend("...");
    list_view_text.prepend("...");
    list_view_text.prepend("...");
    list_view_text.prepend("...");
    list_view_text.prepend("Hello world of C++!");

    Glib::ustring str = "Gkt3 rules! gtkmm and c++ and clion, and much more...";
    str = str.substr(0, 38).append("...");

    list_view_text.prepend(str);
    list_view_text.prepend("Welcome to Hamster");

//    list_view_text
//        .signal_scroll_event()
//        .connect(sigc::mem_fun(*this, &Stage::on_scroll));

    list_view_text
        .signal_selection_received()
        .connect(sigc::mem_fun(*this, &Stage::on_selection));

    button.signal_focus().connect(sigc::mem_fun(*this, &Stage::on_focus));

    show_all();
}

Stage::~Stage() = default;

void Stage::on_search_change()
{
    g_print("%s", search_entry.get_text().c_str());
    g_print(" ");
}

void Stage::on_selection(const Gtk::SelectionData &selection_data, guint time)
{
    g_print("on selection");
    g_print("_");
}

bool Stage::on_focus(Gtk::DirectionType direction)
{
    g_print("%d", direction);
    g_print("on focus");
    return false;
}

void Stage::on_items_select()
{
//    for (int item_idx : list_view_text.get_selected()) {
//        std::cout << "items selected: " << item_idx << "\n";
//    }
    g_print("%s", search_entry.get_text().c_str());
    g_print("");
    for (int item_idx : list_view_text.get_selected()) {
        g_print("%d", item_idx);
        g_print("\n");
    }

}