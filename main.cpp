#include <iostream>
#include <aiecad/core/Application.hpp>

int main(int /*argc*/, char ** /*argv*/) {

    aiecad::ApplicationSpecification spec{
        .title = "AIECAD",
        .winspec.title = "AIECAD",
        .winspec.width = 1512,
        .winspec.height = 887,
        .winspec.vsync = true,
    };

    try {
        aiecad::Application app{ spec };
        return app.run();
    } catch (std::exception & e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
