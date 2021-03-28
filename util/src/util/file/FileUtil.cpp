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
#include "FileUtil.h"

using json = nlohmann::json;

std::string FileUtil::config_dir()
{
    return std::string(getenv("HOME")) + "/.config/hamster";
}

std::string FileUtil::items_json_file()
{
    return config_dir() + "/items.json";
}

void FileUtil::write_items_to_file(Glib::RefPtr<Gtk::ListStore> store)
{
    const auto json_file = items_json_file();
    std::filesystem::create_directory(config_dir());
    std::filesystem::remove(json_file); // Write items to new file always

    std::fstream fs{};
    fs.open(json_file, std::ios::in | std::ios::out | std::ios::app);

    ItemUtil iu{};
    const auto items = iu.items_ready_to_json(store->children());

    json j{};
    j["items"] = items;

    fs << j;
    fs.close();
}

void FileUtil::read_items_from_file()
{
}