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

#ifndef STAGE_H
#define STAGE_H

#include <iostream>
#include <gtkmm-3.0/gtkmm.h>

struct Stage : public Gtk::Box
{
    Stage();
    ~Stage() override;

    void on_items_select();

    Gtk::SearchEntry search_entry;
    Gtk::ScrolledWindow scrolled_window;
    Gtk::ListViewText list_view_text;
    Gtk::Button button;

    void on_selection(const Gtk::SelectionData &selection_data, guint time);
    bool on_focus(Gtk::DirectionType direction);
    void on_search_change();
};

#endif //STAGE_H
