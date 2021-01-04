#include "window.h"


Window::Window()
{
    set_border_width(1);
    set_title("Hamster");
    set_resizable(false);
    set_default_size(320, -1);
    set_position(Gtk::WindowPosition::WIN_POS_MOUSE);
}

Window::~Window() = default;
