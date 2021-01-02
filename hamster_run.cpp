#include <window.h>
#include <stage.h>


int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create("org.gtkmm.examples.base");

    Window window{};
    window.set_border_width(1);
    window.set_title("hamster");
    window.set_resizable(false);
    window.set_default_size(420, -1);

    Stage stage{};
    window.add(stage);

    return app->run(window, argc, argv);
}
