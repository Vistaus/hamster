#ifndef HAMSTER_WINDOW_H
#define HAMSTER_WINDOW_H

#include <iostream>
#include <gtkmm-3.0/gtkmm.h>


struct HamsterWindow: public Gtk::Window
{
    HamsterWindow();
    ~HamsterWindow() override;

    Gtk::Box main_box;
    Gtk::SearchEntry search_entry;
    Gtk::ScrolledWindow scrolled_window;
    Gtk::ListViewText list_view_text;
};


#endif //HAMSTER_WINDOW_H
