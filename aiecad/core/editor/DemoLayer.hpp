#pragma once

#include <aiecad/core/Layer.hpp>
#include <imgui.h>

namespace aiecad {

class DemoLayer : public Layer {
public:
	DemoLayer() : Layer("DemoLayer") {}

	void onImGuiRender() override {
		ImGui::Begin("AIECAD Demo");
		ImGui::Text("Hello from AIECAD!");
		ImGui::Separator();
		ImGui::Text("This is the minimal demo layer.");
		ImGui::End();
	}
};

} // namespace aiecad