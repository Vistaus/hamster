#ifndef STAGE_H
#define STAGE_H

#include <gtkmm-3.0/gtkmm.h>


struct Stage: public Gtk::Box
{
    Stage();
    ~Stage() override;

    Gtk::SearchEntry search_entry;
    Gtk::ScrolledWindow scrolled_window;
    Gtk::ListViewText list_view_text;
};


#endif //STAGE_H
