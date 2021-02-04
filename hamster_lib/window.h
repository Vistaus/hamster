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
 */

#ifndef WINDOW_H
#define WINDOW_H

#include <gtkmm-3.0/gtkmm.h>

struct Window : public Gtk::ApplicationWindow
{
    Window();
    ~Window() override;

    Gtk::HeaderBar headerBar;
    Gtk::MenuButton settingsButton;
    Gtk::Image settingsIcon;
    Gtk::PopoverMenu popoverMenu;
    Gtk::Box popoverBox;
    Gtk::Label preferencesLabel;
    Gtk::Label shortcutsLabel;
    Gtk::Label aboutLabel;
    Gtk::Label quitLabel;
    Gtk::Separator separator;
};

#endif //WINDOW_H
