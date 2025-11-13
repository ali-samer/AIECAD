#include <aiecad/core/editor/EditorLayer.hpp>

#include <imgui.h>

namespace aiecad {

void EditorLayer::onAttach() {
	m_counterPanel = std::make_unique<CounterPanel>(m_eventBus);
}

void EditorLayer::onDetach() {
	m_counterPanel.reset();
}

void EditorLayer::onImGuiRender() {
	if (ImGui::Begin("Counter")) {
		if (m_counterPanel) {
			m_counterPanel->onImGuiRender();
		}
	}
	ImGui::End();
}

} // namespace aiecad