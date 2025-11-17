#pragma once

#include <aiecad/core/Layer.hpp>
#include <aiecad/core/Window.hpp>

namespace aiecad {

class ImGuiLayer : public Layer {
public:
	explicit ImGuiLayer(Window& window);
	~ImGuiLayer() override = default;

	void onAttach() override;
	void onDetach() override;

	void begin();
	void end();

private:
	Window& m_window;
};

} // namespace aiecad