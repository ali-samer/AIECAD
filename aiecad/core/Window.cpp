#include <aiecad/core/Window.hpp>
#include <aiecad/Portability.hpp>

#if AIECAD_WINDOW_BACKEND_GLFW
#	include <aiecad/portability/graphics/GLFWWindow.hpp>
#else
#	error "Unsupported window backend: AIECAD currently supports only GLFW."
#endif

#include <aiecad/core/logging/Logger.hpp>
#include <memory>

namespace aiecad {

std::unique_ptr<Window> Window::Create(const WindowSpecification &win_spec) {
	AIECAD_CORE_INFO("Creating window...");
#if AIECAD_WINDOW_BACKEND_GLFW
	return std::make_unique<GLFWWindow>(win_spec);
#endif
}

} // namespace aiecad