#include <aiecad/ui/ImGuiFramework.hpp>

#include <aiecad/Portability.hpp>
#include <aiecad/core/Window.hpp>
#include <aiecad/core/logging/Logger.hpp>
#include <aiecad/ui/UIStyle.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>

#if AIECAD_RENDER_API_OPENGL
    #include <imgui_impl_opengl3.h>
#elif AIECAD_RENDER_API_METAL
    #include <imgui_impl_metal.h>
#endif

#include <GLFW/glfw3.h>

namespace aiecad {

ImGuiFramework::ImGuiFramework(Window& window)
    : m_window(window) {}

void ImGuiFramework::init() {
    if (m_initialized) {
        AIECAD_CORE_WARN("ImGuiFramework::init() called more than once");
        return;
    }

    AIECAD_CORE_INFO("Initializing ImGui framework");

    initContext();
    initBackends();

    m_initialized = true;
}

void ImGuiFramework::shutdown() {
    if (!m_initialized) {
        return;
    }

    AIECAD_CORE_INFO("Shutting down ImGui framework");

    shutdownBackends();
    shutdownContext();

    m_initialized = false;
}

void ImGuiFramework::initContext() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    UIStyle::ConfigureFont("assets/fonts/ttf/JetBrainsMono-Regular.ttf", 15.0f);
    UIStyle::ApplyAIECADTheme();

    // set ini filename (layout persistence)
    // io.IniFilename = "aiecad_layout.ini";

    AIECAD_CORE_INFO("ImGui context created with docking enabled");
}

void ImGuiFramework::initBackends() {
    GLFWwindow* glfwHandle =
        static_cast<GLFWwindow*>(m_window.getNativeHandle());

    if (!glfwHandle) {
        AIECAD_CORE_FATAL("ImGuiFramework: Window native handle is null");
        throw std::runtime_error("ImGuiFramework: null window handle");
    }

#if AIECAD_RENDER_API_OPENGL
    ImGui_ImplGlfw_InitForOpenGL(glfwHandle, true);
    ImGui_ImplOpenGL3_Init("#version 410");
    AIECAD_CORE_INFO("ImGui backends initialized for GLFW + OpenGL");
#elif AIECAD_RENDER_API_METAL
    // when we add Metal:
    // ImGui_ImplGlfw_InitForOtherBackend(glfwHandle, true);
    // ImGui_ImplMetal_Init(device, renderPassDescriptor);
    static_assert(false, "Metal ImGui backend not implemented yet");
#endif
}

void ImGuiFramework::shutdownBackends() {
#if AIECAD_RENDER_API_OPENGL
    ImGui_ImplOpenGL3_Shutdown();
#elif AIECAD_RENDER_API_METAL
    ImGui_ImplMetal_Shutdown();
#endif

    ImGui_ImplGlfw_Shutdown();
}

void ImGuiFramework::shutdownContext() {
    ImGui::DestroyContext();
}

void ImGuiFramework::beginFrame() {
	if (!m_initialized) {
		AIECAD_CORE_WARN("ImGuiFramework::beginFrame() called before init()");
		return;
	}
	if (ImGui::GetCurrentContext() == nullptr) {
		AIECAD_CORE_WARN("ImGuiFramework::beginFrame() with no ImGui context");
		return;
	}

#if AIECAD_RENDER_API_OPENGL
	ImGui_ImplOpenGL3_NewFrame();
#elif AIECAD_RENDER_API_METAL
	ImGui_ImplMetal_NewFrame();
#endif

    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiFramework::endFrame() {
	if (!m_initialized) {
		AIECAD_CORE_WARN("ImGuiFramework::endFrame() called before init()");
		return;
	}
	if (ImGui::GetCurrentContext() == nullptr) {
		AIECAD_CORE_WARN("ImGuiFramework::endFrame() with no ImGui context");
		return;
	}

	ImGui::Render();

#if AIECAD_RENDER_API_OPENGL
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#elif AIECAD_RENDER_API_METAL
    ImGui_ImplMetal_RenderDrawData(ImGui::GetDrawData());
#endif

    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow* backup = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup);
    }
}

} // namespace aiecad
