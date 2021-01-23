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
 *
 * Authored by: Slawek Tuleja <slawek.tuleja@gmail.com>
 */

#include "window.h"

Window::Window()
{
    set_border_width(1);
    set_title("Hamster");
    set_resizable(false);
    set_default_size(320, -1);
    set_position(Gtk::WindowPosition::WIN_POS_MOUSE);
}

Window::~Window() = default;
