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
#include "ShortcutsWindow.h"

ShortcutsWindow::ShortcutsWindow()
{
    set_title(_("Shortcuts"));

    section.set_name(_("Shortcuts"));
    section.pack_start(app_group);

    app_group.set_name(_("Application"));

    show_hide_app_shortcut.set_name("sdfsadf");
    app_group.pack_start(show_hide_app_shortcut);

    app_group.show_all();
    section.show_all();

    add(section);
}

ShortcutsWindow::~ShortcutsWindow() = default;
