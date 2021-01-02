#ifndef STAGE_H
#define STAGE_H

#include <iostream>
#include <gtkmm-3.0/gtkmm.h>


struct Stage: public Gtk::Box
{
    Stage();
    ~Stage() override;

    void on_items_select();

    Gtk::SearchEntry search_entry;
    Gtk::ScrolledWindow scrolled_window;
    Gtk::ListViewText list_view_text;
    Gtk::Button button;
    bool on_scroll(GdkEventScroll *);
    void on_selection(const Gtk::SelectionData &selection_data, guint time);
};


#endif //STAGE_H
