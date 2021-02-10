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

#ifndef HAMSTER_MAINWINDOW_H
#define HAMSTER_MAINWINDOW_H

#include <gtkmm-3.0/gtkmm.h>
#include <glibmm/i18n.h>

#include "WindowLayout.h"
#include "settings_popover/SettingsMenuButton.h"
#include "about_dialog/AboutDialog.h"
#include "shortcuts_window/ShortcutsWindow.h"
#include "preferences_window/PreferencesWindow.h"

struct MainWindow : public Gtk::Window
{
    MainWindow();

    Gtk::HeaderBar header_bar;
    SettingsMenuButton menu_btn;
    WindowLayout layout;
    AboutDialog about_dialog;
    ShortcutsWindow shortcuts_window;
    PreferencesWindow preferences_window;

    void show_about_dialog();
    void show_shortcuts_window();
    void show_preferences_window();
    void hide_about_dialog(int response_id);
    void hide_shortcuts_window();
    void close_app();
};

#endif //HAMSTER_MAINWINDOW_H
