#pragma once

#include <aiecad/core/Layer.hpp>
#include <aiecad/core/Window.hpp>

namespace aiecad {

class ImGuiFramework final {
public:
	explicit ImGuiFramework(Window& window);
	~ImGuiFramework() = default;

	void init();
	void shutdown();

	void beginFrame();
	void endFrame();

private:
	Window& m_window;
};

} // namespace aiecad