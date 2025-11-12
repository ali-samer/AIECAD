#include <aiecad/core/Window.hpp>
#include <aiecad/Portability.hpp>

#if AIECAD_WINDOW_BACKEND_GLFW
#	include <aiecad/portability/graphics/GLFWWindow.hpp>
#else
#	error "Unsupported window backend: AIECAD currently supports only GLFW."
#endif

#include <memory>

namespace aiecad {

std::unique_ptr<Window> Window::Create(const WindowSpecification &win_spec) {
#if AIECAD_WINDOW_BACKEND_GLFW
	return std::make_unique<GLFWWindow>(win_spec);
#endif
}

} // namespace aiecad