#include "stage.h"


Stage::Stage()
    : search_entry(),
      scrolled_window(),
      list_view_text(1, false, Gtk::SELECTION_MULTIPLE)
{
    set_orientation(Gtk::ORIENTATION_VERTICAL);

    pack_start(search_entry);
    pack_start(scrolled_window);
    scrolled_window.set_size_request(-1, 420);
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

Stage::~Stage() = default;