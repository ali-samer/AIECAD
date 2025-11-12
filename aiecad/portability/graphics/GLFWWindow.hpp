#pragma once

#include <aiecad/core/Window.hpp>
#include <aiecad/core/Specifications.hpp>
#include <GLFW/glfw3.h>
#include <aiecad/Portability.hpp>

namespace aiecad {

class GLFWWindow final : public Window {
public:
	explicit GLFWWindow(const WindowSpecification&);


private:
	static void Init();
};

} // aiecad

