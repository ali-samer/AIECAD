// src/ui/DockSpaceLayer.cpp
#include <aiecad/ui/DockSpace.hpp>
#include <aiecad/core/logging/Logger.hpp>

#include <imgui.h>

namespace aiecad {

DockSpace::DockSpace()
	: Layer("DockSpaceLayer") {}

void DockSpace::onImGuiRender() {
	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDocking;

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	windowFlags |= ImGuiWindowFlags_NoTitleBar
				|  ImGuiWindowFlags_NoCollapse
				|  ImGuiWindowFlags_NoResize
				|  ImGuiWindowFlags_NoMove
				|  ImGuiWindowFlags_NoBringToFrontOnFocus
				|  ImGuiWindowFlags_NoNavFocus;

	// This window will sit under the main menu bar and host the dockspace
	ImGui::Begin("AIECADDockSpaceHost", nullptr, windowFlags);
	ImGui::PopStyleVar(3);

	ImGuiID dockspaceId = ImGui::GetID("AIECADDockSpace");
	ImGuiDockNodeFlags dockFlags = ImGuiDockNodeFlags_None;

	ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), dockFlags);

	ImGui::End();
}

} // namespace aiecad