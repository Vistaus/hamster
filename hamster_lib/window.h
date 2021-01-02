#ifndef WINDOW_H
#define WINDOW_H

#include <gtkmm-3.0/gtkmm.h>


struct Window: public Gtk::Window
{
    Window();
    ~Window() override;
};


#endif //WINDOW_H
