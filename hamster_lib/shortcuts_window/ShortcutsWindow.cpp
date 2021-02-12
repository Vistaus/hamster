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
    set_default_size(540, 320);
    set_resizable(false);
    set_decorated(false);
    set_position(Gtk::WindowPosition::WIN_POS_CENTER_ON_PARENT);

    header_bar.set_show_close_button(true);
    header_bar.set_has_subtitle(false);
    section.property_visible().set_value(true);

    // APPLICATION SHORTCUTS
    show_app_shortcut.property_title().set_value(_("Show application window"));
    show_app_shortcut.property_shortcut_type().set_value(Gtk::SHORTCUT_ACCELERATOR);
    show_app_shortcut.property_accelerator().set_value("<Ctrl><Alt>V");

    show_settings_shortcut.property_title().set_value(_("Open settings menu"));
    show_settings_shortcut.property_shortcut_type().set_value(Gtk::SHORTCUT_ACCELERATOR);
    show_settings_shortcut.property_accelerator().set_value("<Alt>S");

    quit_app_shortcut.property_title().set_value(_("Quit application"));
    quit_app_shortcut.property_shortcut_type().set_value(Gtk::SHORTCUT_ACCELERATOR);
    quit_app_shortcut.property_accelerator().set_value("<Alt>Q");

    app_group.add(show_app_shortcut);
    app_group.add(show_settings_shortcut);
    app_group.add(quit_app_shortcut);

    app_group.property_title().set_value(_("Application"));
    section.add(app_group);

    // TEXT ITEMS SHORTCUTS
    paste_item_shortcut.property_title().set_value(_("Paste item"));
    paste_item_shortcut.property_shortcut_type().set_value(Gtk::SHORTCUT_ACCELERATOR);
    paste_item_shortcut.property_accelerator().set_value("Return");

    select_items_shortcut.property_title().set_value(_("Select items"));
    select_items_shortcut.property_shortcut_type().set_value(Gtk::SHORTCUT_ACCELERATOR);
    select_items_shortcut.property_accelerator().set_value("<Shift>Up Down");

    item_prefix_suffix_shortcut.property_title().set_value(_("Set item prefix or suffix before pasting"));
    item_prefix_suffix_shortcut.property_shortcut_type().set_value(Gtk::SHORTCUT_ACCELERATOR);
    item_prefix_suffix_shortcut.property_accelerator().set_value("<Shift>Return");

    letter_case_shortcut.property_title().set_value(_("Change letter case"));
    letter_case_shortcut.property_shortcut_type().set_value(Gtk::SHORTCUT_ACCELERATOR);
    letter_case_shortcut.property_accelerator().set_value("L");

    delete_item_shortcut.property_title().set_value(_("Delete item"));
    delete_item_shortcut.property_shortcut_type().set_value(Gtk::SHORTCUT_ACCELERATOR);
    delete_item_shortcut.property_accelerator().set_value("Delete");

    items_group.add(paste_item_shortcut);
    items_group.add(select_items_shortcut);
    items_group.add(item_prefix_suffix_shortcut);
    items_group.add(letter_case_shortcut);
    items_group.add(delete_item_shortcut);

    items_group.property_title().set_value(_("Text items"));
    section.add(items_group);

    // MAIN BOX
    v_box.set_margin_top(12);
    v_box.set_margin_right(12);
    v_box.set_margin_left(12);

    v_box.pack_start(header_bar);
    v_box.pack_start(section);
    v_box.show_all();

    add(v_box);
}

