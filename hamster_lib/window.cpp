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

#include "window.h"

Window::Window()
        : headerBar(), settingsButton(), settingsIcon(), popoverMenu(), popoverBox(), preferencesLabel(),
          shortcutsLabel(), aboutLabel(), quitLabel(), separator()
{
    set_border_width(0);
    set_resizable(false);
    set_default_size(360, -1);
    set_position(Gtk::WindowPosition::WIN_POS_MOUSE);

    headerBar.set_show_close_button(true);
    headerBar.set_title("Hamster");
    headerBar.set_subtitle("Clipboard manager");

    preferencesLabel.set_label("Preferences");
    preferencesLabel.set_halign(Gtk::ALIGN_START);
    preferencesLabel.set_margin_bottom(12);
    preferencesLabel.set_margin_right(12);
    preferencesLabel.set_margin_left(12);
    preferencesLabel.set_text_with_mnemonic("Preferences");

    shortcutsLabel.set_label("Shortcuts");
    shortcutsLabel.set_halign(Gtk::ALIGN_START);
    shortcutsLabel.set_margin_bottom(6);
    shortcutsLabel.set_margin_right(12);
    shortcutsLabel.set_margin_left(12);

    aboutLabel.set_label("About");
    aboutLabel.set_halign(Gtk::ALIGN_START);
    aboutLabel.set_margin_top(6);
    aboutLabel.set_margin_bottom(12);
    aboutLabel.set_margin_right(12);
    aboutLabel.set_margin_left(12);

    quitLabel.set_label("Quit");
    quitLabel.set_halign(Gtk::ALIGN_START);
    quitLabel.set_margin_right(12);
    quitLabel.set_margin_left(12);

    popoverBox.set_orientation(Gtk::ORIENTATION_VERTICAL);
    popoverBox.pack_start(preferencesLabel);
    popoverBox.pack_start(shortcutsLabel);

    popoverBox.pack_start(separator);

    popoverBox.pack_start(aboutLabel);
    popoverBox.pack_start(quitLabel);
    popoverBox.show_all();

    popoverBox.set_margin_top(12);
    popoverBox.set_margin_right(12);
    popoverBox.set_margin_bottom(12);
    popoverBox.set_margin_left(12);

    popoverMenu.add(popoverBox);

    settingsIcon.set_from_icon_name("open-menu-symbolic", Gtk::BuiltinIconSize::ICON_SIZE_SMALL_TOOLBAR);
    settingsButton.set_image(settingsIcon);
    settingsButton.set_popover(popoverMenu);

    headerBar.pack_end(settingsButton);
    set_titlebar(headerBar);
}


Window::~Window() = default;
