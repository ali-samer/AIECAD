#include <aiecad/portability/graphics/GLFWWindow.hpp>
#include <aiecad/Portability.hpp>
#include <aiecad/core/logging/Logger.hpp>

#include <GLFW/glfw3.h>
#include <fmt/format.h>

#include <stdexcept>

namespace aiecad {
namespace {
bool         s_glfwInitialized{ false };
unsigned int s_windowCount{ 0 };

void glfwErrorCallback(int err, const char *desc) {
	AIECAD_CORE_ERROR("GLFW Error (code: {}): {}", err, desc);
}

void ensureGlfwInitialized() {
	if (s_glfwInitialized) {
		return;
	}
	if (glfwInit() == GLFW_FALSE) {
		AIECAD_CORE_ERROR("Failed to initialize GLFW");
		throw std::runtime_error("Failed to initialize GLFW");
	}

	glfwSetErrorCallback(glfwErrorCallback);
	s_glfwInitialized = true;
	AIECAD_CORE_INFO("GLFW Initialized");
}

void ensureGlfwTerminated() {
	if (s_glfwInitialized && s_windowCount == 0) {
		glfwTerminate();
		s_glfwInitialized = false;
		AIECAD_CORE_INFO("GLFW Terminated");
	}
}
} // anonymous namespace

GLFWWindow::GLFWWindow(const WindowSpecification &spec)
	: m_window(nullptr)
	  , m_spec(spec) {
	ensureGlfwInitialized();
	s_windowCount++;
	init(spec);
}

GLFWWindow::~GLFWWindow() {
	shutdown();
	if (s_windowCount > 0) {
		s_windowCount--;
	}
	ensureGlfwTerminated();
}

void GLFWWindow::init(const WindowSpecification &spec) {
	std::string err_desc;
	if (!validSpec(spec, &err_desc)) {
		AIECAD_CORE_ERROR("Unable to validate window specification: {}", err_desc);
		throw std::runtime_error("Unable to validate window specification. "
			"Check logs for additional information about error.");
	}

	glfwWindowHint(GLFW_RESIZABLE, spec.resizable ? GLFW_TRUE : GLFW_FALSE);

	// assuming an opengl context is used. Later on, we'd have to support Apple's
	// rending API, Metal.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef AIECAD_PLATFORM_MACOSX
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

	AIECAD_CORE_ASSERT(s_glfwInitialized == true, "GLFW must be initialized "
	                   "before a window is created");
	m_window = glfwCreateWindow(
		static_cast<int>(spec.width),
		static_cast<int>(spec.height),
		spec.title.c_str(),
		nullptr, nullptr
	);

	if (!m_window) {
		AIECAD_CORE_ERROR("Failed to create window.");
		throw std::runtime_error("Failed to create window.");
	}

	glfwMakeContextCurrent(m_window);
	setVSync(spec.vsync);

	glfwSetWindowUserPointer(m_window, this);

	AIECAD_CORE_INFO("Window created: '{}' ({}x{})",
	                 spec.title, spec.width, spec.height);
}

void GLFWWindow::shutdown() {
	if (m_window) {
		AIECAD_CORE_INFO("Destroying window: '{}'", m_spec.title);
		glfwDestroyWindow(m_window);
		m_window = nullptr;
	}
}

void GLFWWindow::onUpdate() {
	// app will call this once per frame
	// it's responsible for polling events and swapping frame buffers.
	glfwPollEvents();
	glfwSwapBuffers(m_window);
}

void GLFWWindow::setVSync(bool enabled) {
	m_spec.vsync = enabled;
	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(enabled ? 1 : 0);
}

bool GLFWWindow::validSpec(const WindowSpecification &spec, std::string *err_desc) noexcept {
	auto set_error = [&](std::string msg) {
		if (err_desc) {
			*err_desc = std::move(msg);
		}
	};

	if (spec.width == 0 || spec.height == 0) {
		set_error(fmt::format(
			"Window dimensions must be non-zero. Requested size -> {}x{}",
			spec.width, spec.height
		));
		return false;
	}

	constexpr std::uint32_t MIN_WINDOW_SIZE = 64;
	if (spec.width < MIN_WINDOW_SIZE || spec.height < MIN_WINDOW_SIZE) {
		set_error(fmt::format(
			"Window dimensions are too small. "
			"Requested size -> {}x{} | Minimum supported -> {}x{}",
			spec.width, spec.height, MIN_WINDOW_SIZE, MIN_WINDOW_SIZE
		));
		return false;
	}

	constexpr std::uint32_t MAX_WINDOW_SIZE = 10000;
	if (spec.width > MAX_WINDOW_SIZE || spec.height > MAX_WINDOW_SIZE) {
		set_error(fmt::format(
			"Window dimensions are unreasonably large. "
			"Requested size -> {}x{} | Max allowed by engine -> {}x{}",
			spec.width, spec.height, MAX_WINDOW_SIZE, MAX_WINDOW_SIZE
		));
		return false;
	}

	if (spec.title.empty()) {
		set_error("Window title must not be empty.");
		return false;
	}

	GLFWmonitor *monitor = glfwGetPrimaryMonitor();
	if (!monitor) {
		set_error("Failed to get primary monitor from GLFW.");
		return false;
	}

	int x, y, maxW, maxH;
	glfwGetMonitorWorkarea(monitor, &x, &y, &maxW, &maxH);

	if (static_cast<int>(spec.width) > maxW || static_cast<int>(spec.height) > maxH) {
		set_error(fmt::format(
			"The following spec contained invalid window dimensions. "
			"Requested size -> {}x{} | Max dimensions supported -> {}x{}",
			spec.width, spec.height, maxW, maxH
		));
		return false;
	}

	return true;
}
} // namespace aiecad
