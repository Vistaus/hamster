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
    set_default_size(526, 512);
    set_resizable(false);
    set_decorated(false);
    set_position(Gtk::WindowPosition::WIN_POS_CENTER_ON_PARENT);

    //ref_settings = Gio::Settings::create("com.github.slawtul.hamster");

    header_bar.set_show_close_button(true);
    header_bar.set_has_subtitle(false);
    header_bar.set_margin_bottom(20);

    // APPLICATION PREFERENCES
    app_label.set_markup(_("<b>Application</b>"));
    app_label.set_halign(Gtk::ALIGN_START);
    app_label.set_margin_bottom(6);
    app_label.set_margin_left(12);
    run_automatically_check.set_label(_("Run automatically on system startup"));
    run_automatically_check.set_active(true);
    always_on_top_check.set_label(_("Always on top"));
    on_mouse_position_check.set_label(_("Place at the current mouse position"));

    app_box.set_margin_left(30);
    app_box.set_margin_right(30);
    app_box.set_spacing(6);
    app_box.pack_start(run_automatically_check);
    app_box.pack_start(always_on_top_check);
    app_box.pack_start(on_mouse_position_check);
    app_box.show_all();

    // ITEMS PREFERENCES
    items_label.set_markup(_("<b>Text items</b>"));
    items_label.set_halign(Gtk::ALIGN_START);
    items_label.set_margin_top(24);
    items_label.set_margin_bottom(6);
    items_label.set_margin_left(12);
    eliminate_spaces_check.set_label(_("Eliminate leading and trailing spaces"));
    eliminate_spaces_check.set_active(true);
    clear_list_check.set_label(_("Clear list on quit"));

    items_box.set_margin_left(30);
    items_box.set_margin_right(30);
    items_box.set_spacing(6);
    items_box.pack_start(eliminate_spaces_check);
    items_box.pack_start(clear_list_check);
    items_box.show_all();

    // LIST SIZE PREFERENCES
    item_list_size_scale.set_digits(0);
    item_list_size_scale.set_range(1, 1024);
    item_list_size_scale.add_mark(1, Gtk::POS_TOP, "");
    item_list_size_scale.add_mark(256, Gtk::POS_TOP, "");
    item_list_size_scale.add_mark(512, Gtk::POS_TOP, "");
    item_list_size_scale.add_mark(768, Gtk::POS_TOP, "");
    item_list_size_scale.add_mark(1024, Gtk::POS_TOP, "");
    item_list_size_scale.set_value(256);

    set_size_label.set_markup(_("<b>Item list size</b>"));
    set_size_label.set_halign(Gtk::ALIGN_START);
    set_size_label.set_margin_top(24);
    set_size_label.set_margin_bottom(6);
    set_size_label.set_margin_left(12);
    scale_box.set_margin_left(30);
    scale_box.set_margin_right(30);
    scale_box.pack_start(item_list_size_scale);
    scale_box.show_all();

    // ITEM PREFERENCES
    item_label.set_markup(_("<b>Text item</b>"));
    item_label.set_halign(Gtk::ALIGN_START);
    item_label.set_margin_top(24);
    item_label.set_margin_bottom(12);
    item_label.set_margin_left(12);
    item_prefix.set_margin_bottom(6);
    item_prefix.set_margin_left(24);
    item_prefix.set_placeholder_text(_("empty"));

    prefix_label.set_label(_("Prefix:"));
    suffix_label.set_label(_("Suffix:"));

    prefix_box.set_halign(Gtk::ALIGN_START);
    prefix_box.pack_start(prefix_label);
    prefix_box.pack_end(item_prefix);
    prefix_box.show_all();

    item_suffix.property_text().set_value("\\n");
    item_suffix.set_margin_left(24);
    suffix_box.set_halign(Gtk::ALIGN_START);
    suffix_box.pack_start(suffix_label);
    suffix_box.pack_start(item_suffix);
    suffix_box.show_all();

    item_box.set_margin_left(30);
    item_box.set_margin_right(30);
    item_box.pack_start(prefix_box);
    item_box.pack_start(suffix_box);
    item_box.show_all();

    // MAIN BOX
    v_box.set_margin_top(12);
    v_box.set_margin_right(12);
    v_box.set_margin_bottom(24);
    v_box.set_margin_left(12);
    v_box.pack_start(header_bar);
    v_box.pack_start(app_label);
    v_box.pack_start(app_box);
    v_box.pack_start(items_label);
    v_box.pack_start(items_box);
    v_box.pack_start(set_size_label);
    v_box.pack_start(scale_box);
    v_box.pack_start(item_label);
    v_box.pack_start(item_box);

    v_box.show_all();

    add(v_box);
}

