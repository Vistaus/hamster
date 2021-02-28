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

#include "MainWindow.h"

MainWindow::MainWindow()
{
    set_border_width(0);
    set_resizable(false);
    set_default_size(360, -1);

    ref_settings = Gio::Settings::create("com.github.slawtul.hamster");

    auto const x = ref_settings->get_int("window-x");
    auto const y = ref_settings->get_int("window-y");

    x == -1 && y == -1 ? set_position(Gtk::WIN_POS_CENTER) : move(x, y);

    header_bar.set_show_close_button(true);
    header_bar.set_title(_("🐹 Hamster"));
    header_bar.set_subtitle(_("Clipboard manager"));
    header_bar.pack_end(menu_btn);
    set_titlebar(header_bar);

    //add_events(Gdk::KEY_PRESS_MASK);

    add(win_body);


    // ABOUT DIALOG
    about_dialog.set_transient_for(*this);
    menu_btn.settings_popover.about_btn.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::show_about_dialog));
    about_dialog.signal_response().connect(sigc::mem_fun(*this, &MainWindow::hide_about_dialog));


    // PREFERENCES WINDOW
    preferences_window.set_transient_for(*this);
    menu_btn.settings_popover.pref_btn
        .signal_clicked()
        .connect(sigc::mem_fun(*this, &MainWindow::show_preferences_win));


    // SHORTCUTS WINDOW
    shortcuts_window.set_transient_for(*this);
    menu_btn.settings_popover.shortcuts_btn
        .signal_clicked()
        .connect(sigc::mem_fun(*this, &MainWindow::show_shortcuts_win));


    // QUIT APP
    menu_btn.settings_popover.quit_btn.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::close_app));
}

void MainWindow::show_about_dialog()
{
    about_dialog.show_all();
    about_dialog.present();
}

void MainWindow::hide_about_dialog(int response_id)
{
    if (response_id == Gtk::ResponseType::RESPONSE_DELETE_EVENT)
    {
        about_dialog.hide();
    }
}

void MainWindow::show_shortcuts_win()
{
    shortcuts_window.show_all();
    shortcuts_window.present();
}

void MainWindow::show_preferences_win()
{
    preferences_window.show_all();
    preferences_window.present();
}

void MainWindow::close_app()
{
    int cur_x, cur_y;
    this->get_position(cur_x, cur_y);
    ref_settings->set_int("window-x", cur_x);
    ref_settings->set_int("window-y", cur_y);

    menu_btn.settings_popover.remove();
    exit(0);
}

bool MainWindow::on_delete_event(GdkEventAny *any_event)
{
    if (any_event == nullptr)
    {
        return false;
    }
    close_app();
    return true;
}
