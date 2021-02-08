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
#ifndef HAMSTER_ABOUTDIALOG_H
#define HAMSTER_ABOUTDIALOG_H

#include <gtkmm-3.0/gtkmm.h>
#include <glibmm/i18n.h>

struct AboutDialog : public Gtk::AboutDialog
{
    AboutDialog();

    ~AboutDialog() override;
};

#endif //HAMSTER_ABOUTDIALOG_H
