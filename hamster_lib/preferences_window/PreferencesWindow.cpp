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
#include "PreferencesWindow.h"

PreferencesWindow::PreferencesWindow()
{
    set_title(_("Preferences"));
    set_default_size(420, 380);
    set_resizable(false);

    app_frame.set_label(_("Application"));
    items_frame.set_label(_("Text items"));
    item_group_frame.set_label(_("Text item group"));

    run_automatically_check.set_label(_("Run automatically on system startup"));
    always_on_top_check.set_label(_("Always on top"));
    on_mouse_position_check.set_label(_("Place at the current mouse position"));

    eliminate_spaces_check.set_label(_("Eliminate leading and trailing spaces"));
    clear_list_check.set_label(_("Clear list on quit"));
    set_size_label.set_label(_("Item list size"));

    prefix_label.set_label(_("Prefix:"));
    suffix_label.set_label(_("Suffix:"));

    item_list_size_scale.set_digits(0);
    item_list_size_scale.set_range(1, 1024);
    item_list_size_scale.add_mark(1, Gtk::POS_TOP, "");
    item_list_size_scale.add_mark(256, Gtk::POS_TOP, "");
    item_list_size_scale.add_mark(512, Gtk::POS_TOP, "");
    item_list_size_scale.add_mark(768, Gtk::POS_TOP, "");
    item_list_size_scale.add_mark(1024, Gtk::POS_TOP, "");
    item_list_size_scale.set_value(256);

    // APPLICATION FRAME
    app_box.set_margin_top(12);
    app_box.set_margin_right(12);
    app_box.set_margin_bottom(12);
    app_box.set_margin_left(12);
    app_box.pack_start(run_automatically_check);
    app_box.pack_start(always_on_top_check);
    app_box.pack_start(on_mouse_position_check);
    app_box.show_all();
    app_frame.set_margin_bottom(12);
    app_frame.set_label_align(0.01, 0.5);
    app_frame.add(app_box);

    // ITEMS FRAME
    items_box.set_margin_top(12);
    items_box.set_margin_left(12);
    items_box.set_margin_right(12);
    items_box.set_margin_bottom(12);
    items_box.pack_start(eliminate_spaces_check);
    items_box.pack_start(clear_list_check);
    items_box.pack_start(set_size_label);
    items_box.pack_start(item_list_size_scale);
    items_box.show_all();
    items_frame.set_margin_bottom(12);
    items_frame.set_label_align(0.01, 0.5);
    items_frame.add(items_box);

    // ITEM GROUP FRAME
    item_prefix.set_margin_bottom(6);
    item_prefix.set_placeholder_text(_("empty"));
    item_group_box.set_margin_top(12);
    item_group_box.set_margin_left(12);
    item_group_box.set_margin_right(12);
    item_group_box.set_margin_bottom(12);

    prefix_box.pack_start(prefix_label);
    prefix_box.pack_end(item_prefix);
    prefix_box.show_all();

    item_suffix.property_text().set_value("\\n");
    suffix_box.pack_start(suffix_label);
    suffix_box.pack_start(item_suffix);
    suffix_box.show_all();

    item_group_box.pack_start(prefix_box);
    item_group_box.pack_start(suffix_box);
    item_group_box.show_all();
    item_group_frame.set_label_align(0.01, 0.5);
    item_group_frame.add(item_group_box);

    v_box.set_margin_top(12);
    v_box.set_margin_right(12);
    v_box.set_margin_bottom(12);
    v_box.set_margin_left(12);
    v_box.pack_start(app_frame);
    v_box.pack_start(items_frame);
    v_box.pack_start(item_group_frame);
    v_box.show_all();

    add(v_box);
}

PreferencesWindow::~PreferencesWindow() = default;
