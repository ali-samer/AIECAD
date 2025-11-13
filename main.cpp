// main.cpp
#include <iostream>
#include <aiecad/core/Application.hpp>
#include <aiecad/core/Specifications.hpp>  // AppSpecification

int main(int /*argc*/, char ** /*argv*/) {
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
    return 0;
}
