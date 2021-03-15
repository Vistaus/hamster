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

#ifndef HAMSTER_WINDOW_BODY_H
#define HAMSTER_WINDOW_BODY_H

#include <glibmm/i18n.h>
#include <gtkmm-3.0/gtkmm.h>
#include <X11/Intrinsic.h>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <algorithm>
#include <regex>
#include <chrono>
#include <thread>
#include "util/text/TextUtil.h"
#include "item_details_window/ItemDetailsWindow.h"

enum struct SelectionOrder
{
    SHIFT_UP, SHIFT_DOWN
};

enum struct StoreType
{
    PRIMARY, SECONDARY
};

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
    Glib::RefPtr<Gtk::ListStore> ref_primary_item_store;   // All items go here
    Glib::RefPtr<Gtk::ListStore> ref_secondary_item_store; // Searched items go here only
    Glib::RefPtr<Gtk::Clipboard> ref_clipboard;
    Glib::RefPtr<Gio::Settings> ref_settings;

    SelectionOrder selection_order;
    StoreType store_type;

    ItemDetailsWindow item_details_window;

    static void send_ctrl_v_key_event();

    void on_clipboard_change(GdkEventOwnerChange* event);
    void on_search_change();
    bool on_search_entry_event(GdkEvent* gdk_event);

    bool on_item_list_key_press(GdkEventKey* key_event);
    bool on_item_list_event(GdkEvent* gdk_event);

    void show_item_details_window(const Glib::ustring& text);

    void transform_to_lowercase();
    void transform_to_uppercase();
    void delete_items();

    // HELPER METHODS
    Gtk::TreeRow get_row(const Gtk::TreeModel::Path& path);
    std::vector<Gtk::TreeModel::Path> get_selected_rows();

    void sync_stores(void (WindowBody::* f)());
};

#endif //HAMSTER_WINDOW_BODY_H
