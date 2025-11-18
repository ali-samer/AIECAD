#pragma once

#include <aiecad/macros/Macros.hpp>
#include <cstdint>

namespace aiecad {

class Window;

class ImGuiFramework final {
public:
	explicit ImGuiFramework(Window& window);
	~ImGuiFramework() = default;

	AIECAD_DELETE_COPY_AND_MOVE(ImGuiFramework);

	void init();
	void shutdown();

	void beginFrame();
	void endFrame();

private:
	void initContext();        // ImGui::CreateContext + IO flags, style, fonts
	void initBackends();       // ImGui_ImplGlfw + renderer backend
	void shutdownBackends();
	void shutdownContext();

	Window& m_window;
	bool    m_initialized{false};
};

} // namespace aiecad