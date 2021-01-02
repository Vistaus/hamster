#ifndef HAMSTER_WINDOW_H
#define HAMSTER_WINDOW_H

#include <iostream>
#include <gtkmm-3.0/gtkmm.h>


struct HamsterWindow: public Gtk::Window
{
    HamsterWindow();
    ~HamsterWindow() override;

    void on_button_clicked(const Glib::ustring &data);

    Gtk::Box box;
    Gtk::SearchEntry search_entry;
    Gtk::ListBox list_box;
    Gtk::ListBoxRow row;
    Gtk::Label label;
};


#endif //HAMSTER_WINDOW_H
