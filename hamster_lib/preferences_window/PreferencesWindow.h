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
#ifndef HAMSTER_PREFERENCESWINDOW_H
#define HAMSTER_PREFERENCESWINDOW_H

#include <gtkmm-3.0/gtkmm.h>
#include <glibmm/i18n.h>

struct PreferencesWindow : public Gtk::Window
{
    PreferencesWindow();

    ~PreferencesWindow() override;

    Gtk::HeaderBar header_bar;
    Gtk::VBox v_box;

    Gtk::Label app_label;
    Gtk::Label items_label;
    Gtk::Label set_size_label;
    Gtk::Label item_label;

    Gtk::VBox app_box;
    Gtk::VBox items_box;
    Gtk::VBox scale_box;
    Gtk::VBox item_box;

    Gtk::CheckButton run_automatically_check;
    Gtk::CheckButton always_on_top_check;
    Gtk::CheckButton on_mouse_position_check;

    Gtk::CheckButton eliminate_spaces_check;
    Gtk::CheckButton clear_list_check;
    Gtk::Scale item_list_size_scale;

    Gtk::Box prefix_box;
    Gtk::Box suffix_box;
    Gtk::Label prefix_label;
    Gtk::Label suffix_label;
    Gtk::Entry item_prefix;
    Gtk::Entry item_suffix;
};

#endif //HAMSTER_PREFERENCESWINDOW_H
