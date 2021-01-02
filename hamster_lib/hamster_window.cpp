#include "hamster_window.h"


HamsterWindow::HamsterWindow()
    : main_box(Gtk::Orientation::ORIENTATION_VERTICAL),
      search_entry(),
      scrolled_window(),
      list_view_text(1, false, Gtk::SELECTION_MULTIPLE)
{
    set_title("Hamster - clipboard manager");
    set_resizable(false);

    add(main_box);
    set_default_size(420, -1);
    main_box.pack_start(search_entry);
    main_box.pack_start(scrolled_window);
    scrolled_window.set_size_request(-1, 600);
    scrolled_window.add(list_view_text);

    list_view_text.set_column_title(0, "Items");
    list_view_text.prepend("...");
    list_view_text.prepend("...");
    list_view_text.prepend("...");
    list_view_text.prepend("...");
    list_view_text.prepend("...");
    list_view_text.prepend("...");
    list_view_text.prepend("...");
    list_view_text.prepend("...");
    list_view_text.prepend("...");
    list_view_text.prepend("...");
    list_view_text.prepend("...");
    list_view_text.prepend("...");
    list_view_text.prepend("...");
    list_view_text.prepend("...");
    list_view_text.prepend("...");
    list_view_text.prepend("Hello world of C++!");
    list_view_text.prepend("Gkt3 rules!");
    list_view_text.prepend("Welcome to Hamster");

    show_all();
}

HamsterWindow::~HamsterWindow() = default;
