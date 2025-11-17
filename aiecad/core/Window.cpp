#include <aiecad/core/Window.hpp>
#include <aiecad/Portability.hpp>

#if AIECAD_WINDOW_BACKEND_GLFW
#    include <aiecad/portability/graphics/GLFWWindow.hpp>
#else
#    error "Unsupported window backend: AIECAD currently supports only GLFW."
#endif

#include <aiecad/core/logging/Logger.hpp>

namespace aiecad {

std::unique_ptr<Window> Window::Create(const WindowSpecification& spec) {
	AIECAD_CORE_INFO("Creating window: '{}' ({}x{})",
					 spec.title, spec.width, spec.height);

#if AIECAD_WINDOW_BACKEND_GLFW
	return std::make_unique<GLFWWindow>(spec);
#endif
}

} // namespace aiecad