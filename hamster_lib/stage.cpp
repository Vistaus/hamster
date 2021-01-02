#include "stage.h"


Stage::Stage()
    : search_entry(),
      scrolled_window(),
      list_view_text(1, false, Gtk::SELECTION_MULTIPLE),
      button("Ok")
{
    set_orientation(Gtk::ORIENTATION_VERTICAL);

    pack_start(search_entry);
    pack_start(scrolled_window);
    pack_start(button);

    button.signal_clicked().connect(sigc::mem_fun(*this, &Stage::on_items_select));

    scrolled_window.set_size_request(-1, 420);
    scrolled_window.add(list_view_text);

    list_view_text.set_column_title(0, "Items");
    list_view_text.set_enable_search(false);

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

    list_view_text.signal_scroll_event().connect(sigc::mem_fun(*this, &Stage::on_scroll));
    list_view_text.signal_selection_received().connect(sigc::mem_fun(*this, &Stage::on_selection));

    show_all();
}

Stage::~Stage() = default;

void Stage::on_selection(const Gtk::SelectionData &selection_data, guint time)
{
    g_print("on selection");
    g_print("");
}

bool Stage::on_scroll(GdkEventScroll *scroll_event)
{
    if (scroll_event->direction == GdkScrollDirection::GDK_SCROLL_DOWN) {
        g_print("scroll_down");
    }
    if (scroll_event->direction == GdkScrollDirection::GDK_SCROLL_UP) {
        g_print("scroll_up");
    }
    g_print("scroll");
    g_print("");
    return true;
}

void Stage::on_items_select()
{
//    for (int item_idx : list_view_text.get_selected()) {
//        std::cout << "items selected: " << item_idx << "\n";
//    }
    for (int item_idx : list_view_text.get_selected()) {
        g_print("%d", item_idx);
        g_print("\n");
    }

}
