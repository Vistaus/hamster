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

#ifndef HAMSTER_WINDOWLAYOUT_H
#define HAMSTER_WINDOWLAYOUT_H

#include <iostream>
#include <gtkmm-3.0/gtkmm.h>

struct WindowLayout : public Gtk::VBox
{
    WindowLayout();

    Gtk::SearchEntry search_entry;
    Gtk::ScrolledWindow scrolled_win;
    Gtk::ListViewText item_list;
    Gtk::Separator separator;

    void on_search_change();
};

#endif //HAMSTER_WINDOWLAYOUT_H
