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
#ifndef HAMSTER_TEXTUTIL_H
#define HAMSTER_TEXTUTIL_H

#include <regex>
#include <gtkmm-3.0/gtkmm.h>

struct TextUtil
{
    Glib::ustring join_lines(Glib::ustring &text, uint n_letters);
    Glib::ustring trim_str(const Glib::ustring &text);
    Glib::ustring sub_str(const Glib::ustring &text, uint n_letters, const Glib::ustring &end_text);
    bool has_only_spaces(const Glib::ustring &text);
};

#endif //HAMSTER_TEXTUTIL_H
