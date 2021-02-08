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

#include "MainWindow.h"

MainWindow::MainWindow()
{
    set_border_width(0);
    set_resizable(false);
    set_default_size(360, -1);
    set_position(Gtk::WindowPosition::WIN_POS_CENTER_ALWAYS);

    header_bar.set_show_close_button(true);
    header_bar.set_title(_("Hamster"));
    header_bar.set_subtitle(_("Clipboard manager"));
    header_bar.pack_end(settings_btn);
    set_titlebar(header_bar);

    add(layout);

    // About dialog
    about_dialog.set_transient_for(*this);
    settings_btn.settings_popover.about_btn
            .signal_clicked()
            .connect(sigc::mem_fun(*this, &MainWindow::show_about_dialog));

    // Preferences window

    // Shortcuts window
}

MainWindow::~MainWindow() = default;

void MainWindow::show_about_dialog()
{
    about_dialog.show();
    about_dialog.present();
}