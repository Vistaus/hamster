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
        : headerBar(), settingsButton(), settingsIcon(), popoverMenu(), popoverBox(), separator(), menu(), menuItem()
        , modelButton(), modelButton1()
          , modelButton2(), modelButton3()
{
    set_border_width(0);
    set_resizable(false);
    set_default_size(360, -1);
    set_position(Gtk::WindowPosition::WIN_POS_MOUSE);

    headerBar.set_show_close_button(true);
    headerBar.set_title("Hamster");
    headerBar.set_subtitle("Clipboard manager");

    popoverBox.set_orientation(Gtk::ORIENTATION_VERTICAL);

    menuItem.set_label("Preferences...");

    modelButton.property_text().set_value("Preferences");
    modelButton1.property_text().set_value("Shortcuts");
    modelButton2.property_text().set_value("About");
    modelButton3.property_text().set_value("Quit");


    popoverBox.set_margin_top(12);
    popoverBox.set_margin_right(12);
    popoverBox.set_margin_bottom(12);
    popoverBox.set_margin_left(12);

    popoverBox.pack_start(modelButton);
    popoverBox.pack_start(modelButton1);
    popoverBox.pack_start(separator);
    popoverBox.pack_start(modelButton2);
    popoverBox.pack_start(modelButton3);
    popoverBox.show_all();

    popoverMenu.add(popoverBox);

    settingsIcon.set_from_icon_name("open-menu-symbolic", Gtk::BuiltinIconSize::ICON_SIZE_SMALL_TOOLBAR);
    settingsButton.set_image(settingsIcon);
    settingsButton.set_popover(popoverMenu);

    headerBar.pack_end(settingsButton);
    set_titlebar(headerBar);
}


Window::~Window() = default;
