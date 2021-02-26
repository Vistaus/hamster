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

#ifndef HAMSTER_WINDOWBODY_H
#define HAMSTER_WINDOWBODY_H

#include <iostream>
#include <gtkmm-3.0/gtkmm.h>

struct ItemModelColumns : public Gtk::TreeModel::ColumnRecord
{
    Gtk::TreeModelColumn<Glib::ustring> item_display_value; // Modified clipboard text value showed in list view widget
    Gtk::TreeModelColumn<Glib::ustring> item_value; // Original clipboard text value

    ItemModelColumns()
    {
        add(item_display_value);
        add(item_value);
    }
};

struct WindowBody : public Gtk::VBox
{
    WindowBody();

    Gtk::SearchEntry search_entry;
    Gtk::ScrolledWindow scrolled_win;
    Gtk::Separator separator;

    ItemModelColumns columns;
    Gtk::ListViewText item_list;
    Glib::RefPtr<Gtk::ListStore> ref_item_store;
    Glib::RefPtr<Gtk::Clipboard> ref_clipboard;

    void on_search_change();
    void on_clipboard_change(GdkEventOwnerChange* event) const;
};

#endif //HAMSTER_WINDOWBODY_H
