#include <aiecad/ui/ImGuiFramework.hpp>
#include <aiecad/ui/UIStyle.hpp>
#include <aiecad/core/logging/Logger.hpp>
#include <aiecad/Portability.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>

#if AIECAD_RENDER_API_OPENGL
	#include <imgui_impl_opengl3.h>
#elif AIECAD_RENDER_API_METAL
	#include <imgui_impl_metal.h>
#endif

namespace aiecad {

ImGuiFramework::ImGuiFramework(Window& window)
	: m_window(window) {}

void ImGuiFramework::init() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	GLFWwindow* glfwHandle =
		static_cast<GLFWwindow*>(m_window.getNativeHandle());

#if AIECAD_RENDER_API_OPENGL
	ImGui_ImplGlfw_InitForOpenGL(glfwHandle, true);
	ImGui_ImplOpenGL3_Init("#version 410");
#elif AIECAD_RENDER_API_METAL
	ImGui_ImplGlfw_InitForOtherBackend(glfwHandle, true);
	ImGui_ImplMetal_Init(/* metal device / layer later */);
#endif

	AIECAD_CORE_INFO("ImGuiLayer attached");

	// TODO: applying styles must come with a mechanism for booting up.
	// This is temporary patch
	UIStyle::ApplyDarkTheme();
	AIECAD_INFO("Applied Dark theme to the UI");
}

void ImGuiFramework::shutdown() {
#if AIECAD_RENDER_API_OPENGL
	ImGui_ImplOpenGL3_Shutdown();
#elif AIECAD_RENDER_API_METAL
	ImGui_ImplMetal_Shutdown();
#endif

	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	AIECAD_CORE_INFO("Shutting down dear ImGui rendering");
}

void ImGuiFramework::beginFrame() {
#if AIECAD_RENDER_API_OPENGL
	ImGui_ImplOpenGL3_NewFrame();
#elif AIECAD_RENDER_API_METAL
	ImGui_ImplMetal_NewFrame();
#endif

	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void ImGuiFramework::endFrame() {
	ImGui::Render();

#if AIECAD_RENDER_API_OPENGL
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#elif AIECAD_RENDER_API_METAL
	ImGui_ImplMetal_RenderDrawData(ImGui::GetDrawData());
#endif
}

} // namespace aiecad