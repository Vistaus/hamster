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
    set_default_size(420, -1);
    set_resizable(false);
    set_decorated(false);
    set_position(Gtk::WindowPosition::WIN_POS_CENTER_ON_PARENT);
    header_bar.set_show_close_button(true);
    header_bar.set_has_subtitle(false);

    // APPLICATION SHORTCUTS
    app_label.set_markup(_("<b>Application</b>"));
    app_label.set_halign(Gtk::ALIGN_START);
    app_box.set_margin_top(12);
    app_box.set_margin_right(12);
    app_box.set_margin_bottom(12);
    app_box.set_margin_left(12);
    show_app_shortcut.set_markup(_("Show application window <b>CTRL+ALT+V</b>"));
    show_app_shortcut.set_halign(Gtk::ALIGN_START);
    show_settings_shortcut.set_markup(_("Open settings menu <b>ALT+S</b>"));
    show_settings_shortcut.set_halign(Gtk::ALIGN_START);
    quit_app_shortcut.set_markup(_("Quit application <b>ALT+Q</b>"));
    quit_app_shortcut.set_halign(Gtk::ALIGN_START);
    app_box.pack_start(show_app_shortcut);
    app_box.pack_start(show_settings_shortcut);
    app_box.pack_start(quit_app_shortcut);
    app_box.show_all();

    // ITEMS SHORTCUTS
    items_label.set_markup(_("<b>Text items</b>"));
    items_label.set_halign(Gtk::ALIGN_START);
    items_box.set_margin_top(12);
    items_box.set_margin_right(12);
    items_box.set_margin_bottom(12);
    items_box.set_margin_left(12);
    paste_item_shortcut.set_markup(_("Paste item <b>ENTER</b>"));
    paste_item_shortcut.set_halign(Gtk::ALIGN_START);
    delete_item_shortcut.set_markup(_("Remove item <b>DEL</b>"));
    delete_item_shortcut.set_halign(Gtk::ALIGN_START);
    select_items_shortcut.set_markup(_("Select items <b>SHIFT+&#8593;</b> or <b>SHIFT+&#8595;</b>"));
    select_items_shortcut.set_halign(Gtk::ALIGN_START);
    group_items_shortcut.set_markup(_("Set item prefix or suffix before pasting <b>G</b>"));
    group_items_shortcut.set_halign(Gtk::ALIGN_START);

    items_box.pack_start(paste_item_shortcut);
    items_box.pack_start(select_items_shortcut);
    items_box.pack_start(group_items_shortcut);
    items_box.pack_start(delete_item_shortcut);
    items_box.show_all();

    // MAIN BOX
    v_box.set_margin_top(12);
    v_box.set_margin_right(12);
    v_box.set_margin_bottom(12);
    v_box.set_margin_left(12);
    v_box.pack_start(header_bar);
    v_box.pack_start(app_label);
    v_box.pack_start(app_box);
    v_box.pack_start(items_label);
    v_box.pack_start(items_box);

    v_box.show_all();

    add(v_box);
}

ShortcutsWindow::~ShortcutsWindow() = default;
