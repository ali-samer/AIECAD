// aiecad/editor/EmptyLayer.hpp

#pragma once
#include <aiecad/core/Layer.hpp>
#include <imgui.h>

namespace aiecad {

class EmptyLayer : public Layer {
public:
	EmptyLayer() : Layer("EmptyLayer") {}

	void onImGuiRender() override {
		ImGui::Begin("Empty");
		ImGui::Text("AIECAD is running!");
		ImGui::End();
	}
};

}