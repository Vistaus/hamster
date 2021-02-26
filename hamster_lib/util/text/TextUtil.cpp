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
#include "TextUtil.h"

Glib::ustring TextUtil::sub_str(const Glib::ustring &text, uint n_letters, const Glib::ustring &end)
{
    if (text.length() > n_letters)
    {
        return text.substr(0, n_letters).append(end);
    }
    return text;
}

bool TextUtil::has_only_spaces(const Glib::ustring &text)
{
    return text.find_first_not_of(" \t\n\v\f\r") == Glib::ustring::npos;
}

Glib::ustring TextUtil::join_lines(Glib::ustring &text, uint n_letters)
{
    const auto re = std::regex{"\\s{1,}"};
    return std::regex_replace(text.substr(0, n_letters).c_str(), re, " ");
}

Glib::ustring TextUtil::trim_str(const Glib::ustring &text)
{
    const auto whitespaces = " \t";
    const auto begin = text.find_first_not_of(whitespaces);
    if (begin == std::string::npos)
    {
        return ""; // No content
    }
    const auto end = text.find_last_not_of(whitespaces);
    const auto range = end - begin + 1;
    return text.substr(begin, range);
}