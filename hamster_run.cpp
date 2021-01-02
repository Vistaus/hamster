#include <hamster_window.h>


int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create("org.gtkmm.examples.base");
    HamsterWindow window{};
    return app->run(window, argc, argv);
}
