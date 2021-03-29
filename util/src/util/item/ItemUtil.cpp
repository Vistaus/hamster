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
#include "ItemUtil.h"

std::vector<std::map<std::string, std::string>> ItemUtil::items_ready_to_json(const Gtk::TreeModel::Children& rows)
{
    ItemModelColumns columns;
    std::vector<std::map<std::string, std::string>> container {};
    for (const auto& row : rows)
    {
        const auto display_value = row.get_value(columns.item_display_value);
        const auto value = row.get_value(columns.item_value);
        if (value.length() == 0)
        {
            continue;
        }
        std::map<std::string, std::string> item {{"display_value", display_value},
                                                 {"value",         value}};
        container.emplace_back(item);
    }
    return container;
}
