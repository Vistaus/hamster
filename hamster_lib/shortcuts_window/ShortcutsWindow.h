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
#ifndef HAMSTER_SHORTCUTSWINDOW_H
#define HAMSTER_SHORTCUTSWINDOW_H

#include <gtkmm-3.0/gtkmm.h>
#include <glibmm/i18n.h>

struct ShortcutsWindow : public Gtk::Window
{
    ShortcutsWindow();

    ~ShortcutsWindow() override;

    Gtk::Label app_label;
    Gtk::Label items_label;
    Gtk::VBox app_box;
    Gtk::Label show_app_shortcut;
    Gtk::Label show_settings_shortcut;
    Gtk::Label quit_app_shortcut;

    Gtk::Label paste_item_shortcut;
    Gtk::Label select_items_shortcut;
    Gtk::Label group_items_shortcut;
    Gtk::Label delete_item_shortcut;

    Gtk::VBox items_box;

    Gtk::VBox v_box;
    Gtk::HeaderBar header_bar;
};

#endif //HAMSTER_SHORTCUTSWINDOW_H
