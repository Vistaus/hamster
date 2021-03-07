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

    (x == -1 && y == -1) ? set_position(Gtk::WIN_POS_CENTER) : move(x, y);

    header_bar.set_show_close_button(true);
    header_bar.set_title(_("🐹 Hamster"));
    header_bar.set_subtitle(_("Clipboard manager"));
    header_bar.pack_end(menu_btn);
    set_titlebar(header_bar);

    add(win_body);

    this->signal_key_press_event().connect(sigc::mem_fun(*this, &MainWindow::on_main_window_key_press));

    // ABOUT DIALOG
    about_dialog.set_transient_for(*this);
    menu_btn.settings_popover.about_btn.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::show_about_dialog));
    about_dialog.signal_response().connect(sigc::mem_fun(*this, &MainWindow::hide_about_dialog));

    // PREFERENCES WINDOW
    preferences_window.set_transient_for(*this);
    menu_btn.settings_popover.pref_btn.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::show_preferences_win));

    // SHORTCUTS WINDOW
    shortcuts_window.set_transient_for(*this);
    menu_btn.settings_popover.shortcuts_btn.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::show_shortcuts_win));

    // QUIT APP
    menu_btn.settings_popover.quit_btn.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::close_app));
}

void MainWindow::show_about_dialog()
{
    about_dialog.show();
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
    int win_x, win_y;
    this->get_position(win_x, win_y);
    ref_settings->set_int("window-x", win_x);
    ref_settings->set_int("window-y", win_y);

    exit(0);
}

bool MainWindow::on_main_window_key_press(GdkEventKey* key_event)
{
    if (key_event == nullptr)
    {
        return false;
    }

    const auto ALT_MASK = 24;  // On modern PC

    // 'ALT + P' KEYS PRESSED (show properties window)
    if ((key_event->state == ALT_MASK || key_event->state == GDK_MOD1_MASK) && key_event->keyval == GDK_KEY_p)
    {
        show_preferences_win();
        return true;
    }

    // 'ALT + Q' KEYS PRESSED (quit application)
    if ((key_event->state == ALT_MASK || key_event->state == GDK_MOD1_MASK) && key_event->keyval == GDK_KEY_q)
    {
        close_app();
        return true;
    }

    return false;
}

bool MainWindow::on_delete_event(GdkEventAny* any_event)
{
    if (any_event == nullptr)
    {
        return false;
    }
    close_app();
    return true;
}
