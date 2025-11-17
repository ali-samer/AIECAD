#include <iostream>
#include <aiecad/core/Window.hpp>

int main(int /*argc*/, char ** /*argv*/) {
    /*
    aiecad::ApplicationSpecification spec{
        .name = "AIECAD",
        .window_spec.width = 1600,
        .window_spec.height = 900,
        .window_spec.vSync = true,
        .maximized = false
    };

    try {
        aiecad::Application app{ spec };
        return app.run();
    } catch (std::exception & e) {
        std::cerr << e.what() << std::endl;
    }
    */

    using namespace aiecad;
    WindowSpecification spec {};
    spec.title = "aiecad";
    spec.width = 128U;
    spec.height = 128U;
    auto window = Window::Create(spec);
    while (true) {
        window->onUpdate();
    }
    return 0;
}
