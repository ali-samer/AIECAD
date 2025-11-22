#include <aiecad/ui/panels/ProjectExplorer.hpp>
#include <aiecad/core/events/Events.hpp>

#include <aiecad/core/events/EventBus.hpp>

namespace aiecad {

ProjectExplorer::ProjectExplorer(EventBus &bus) : m_bus(bus) {
	m_toggleSubEvent = m_bus.subscribe<TogglePanelEvent>(
		[&](const TogglePanelEvent& event) {
		if (event.id == id()) {
			toggleVisibility();
		}
	});
}

void ProjectExplorer::onImGuiRender() {
	if(ImGui::Begin("dummy window"))
	{
		if(ImGui::Button("open file dialog"))
			m_fileDialog.Open();
	}
	ImGui::End();

	m_fileDialog.Display();

	if(m_fileDialog.HasSelected())
	{
		m_fileDialog.ClearSelected();
	}
}

} // namespace aiecad