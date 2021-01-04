#include <window.h>
#include <stage.h>


int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create("com.github.slawtul.hamster");

    Stage stage{};

    Window window{};
    window.add(stage);

    return app->run(window, argc, argv);
}
