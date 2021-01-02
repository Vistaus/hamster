#include "hamster_window.h"


HamsterWindow::HamsterWindow()
    : box(Gtk::Orientation::ORIENTATION_VERTICAL),
      search_entry(),
      list_box(),
      row(),
      label("hello world")
{
    set_title("Hamster - clipboard manager");
    set_resizable(true);
    set_default_size(420, 420);
    set_border_width(12);
    add(box);
    box.pack_start(search_entry);

    row.add(label);
    row.set_halign(Gtk::ALIGN_START);
    list_box.append(row);
    list_box.set_selection_mode(Gtk::SelectionMode::SELECTION_MULTIPLE);

    box.pack_start(list_box);

    show_all();
}

void HamsterWindow::on_button_clicked(const Glib::ustring &data)
{
    std::cout << "Button clicked " << data << "\n";
}

HamsterWindow::~HamsterWindow() = default;
