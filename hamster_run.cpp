#include <hamster.h>


int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create("org.gtkmm.examples.base");
    hamster_window hw{};
    return app->run(hw, argc, argv);
}
