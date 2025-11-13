#include <aiecad/core/logging/Logger.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <aiecad/portability/graphics/GLFWWindow.hpp>

#include <stdexcept>

namespace aiecad {

static bool s_glfwInitialized = false;
static std::uint32_t s_windowCount = 0;

static void glfwErrorCallback(int err, const char* desc) {
    AIECAD_CORE_ERROR("GLFW Error (code: {}): {}", err, desc);
}

GLFWWindow::GLFWWindow(const WindowSpecification& spec) : m_winSpec(spec) {
    init(spec);
}

GLFWWindow::~GLFWWindow() {
    shutdown();
}

void GLFWWindow::init(const WindowSpecification& spec) {
    if (!s_glfwInitialized) {
        if (glfwInit() == GLFW_FALSE) {
            AIECAD_CORE_FATAL("Failed to initialize GLFW");
            throw std::runtime_error("Failed to initialize GLFW");
        }
        glfwSetErrorCallback(glfwErrorCallback);
        s_glfwInitialized = true;
        AIECAD_CORE_INFO("GLFW Initialized");
    }

    s_windowCount++;

#ifdef __APPLE__
    AIECAD_CORE_INFO("MacOS detected. Setting additional window hints for compatibility");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
    // Other platforms: choose whatever you like (4.5 core is fine)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    int width  = static_cast<int>(spec.width);
    int height = static_cast<int>(spec.height);

    GLFWwindow* window = glfwCreateWindow(width, height, spec.title.c_str(), nullptr, nullptr);
    if (!window) {
        throw std::runtime_error("Failed to create GLFW window");
    }

    m_window = window;

    glfwMakeContextCurrent(m_window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
    glfwSwapInterval(spec.vSync ? 1 : 0);

    m_data.title  = spec.title;
    m_data.width  = spec.width;
    m_data.height = spec.height;
    m_data.vsync  = spec.vSync;

    // we have to store pointer to WindowData so callbacks can access it.
    glfwSetWindowUserPointer(m_window, &m_data);

    /* --- GLFW callbacks --- */

    // Resize
    glfwSetWindowSizeCallback(
        m_window,
        [](GLFWwindow* win, int w, int h) {
            auto* data = static_cast<WindowData*>(glfwGetWindowUserPointer(win));
            data->width  = static_cast<std::uint32_t>(w);
            data->height = static_cast<std::uint32_t>(h);

            if (data->eventCallback) {
                BackendWindowEvent ev;
                ev.type   = BackendWindowEventType::Resize;
                ev.width  = data->width;
                ev.height = data->height;
                data->eventCallback(ev);
            }
        }
    );

    // Close
    glfwSetWindowCloseCallback(
        m_window,
        [](GLFWwindow* win) {
            auto* data = static_cast<WindowData*>(glfwGetWindowUserPointer(win));
            if (data->eventCallback) {
                BackendWindowEvent ev;
                ev.type = BackendWindowEventType::Close;
                data->eventCallback(ev);
            }
        }
    );

    // TODO:
    // We can add more callbacks later for key, mouse, scroll, etc,
    // and map them into the backend event structs or directly
    // publish to EventBus
}

void GLFWWindow::shutdown() {
    if (m_window) {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
        s_windowCount--;

        if (s_windowCount == 0) {
            glfwTerminate();
            s_glfwInitialized = false;
        }
    }
}

void GLFWWindow::onUpdate() {
    glfwPollEvents();
    glfwSwapBuffers(m_window);
}

void GLFWWindow::setVSync(bool enabled) {
    m_data.vsync = enabled;
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(enabled ? 1 : 0);
}

} // namespace aiecad