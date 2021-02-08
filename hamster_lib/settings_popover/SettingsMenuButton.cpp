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
#include "SettingsMenuButton.h"

SettingsMenuButton::SettingsMenuButton()
{
    btn_icon.set_from_icon_name("open-menu-symbolic", Gtk::BuiltinIconSize::ICON_SIZE_SMALL_TOOLBAR);
    set_image(btn_icon);
    set_popover(settings_popover);
}

SettingsMenuButton::~SettingsMenuButton() = default;
