#include <aiecad/core/logging/Logger.hpp>
#include <aiecad/ui/PanelHostLayer.hpp>
#include <aiecad/core/events/Events.hpp>

#include <aiecad/ui/panels/DeviceConnectionPanel.hpp>
#include <aiecad/ui/panels/ProjectExplorer.hpp>

namespace aiecad {

PanelHostLayer::PanelHostLayer(EventBus& bus, PanelManager& manager)
	: Layer("PanelHostLayer")
	, m_bus(bus)
	, m_panelManager(manager) {


	/*
	 * Experimenting with plugable UI. Use this strategy for panels that are
	 * not often used, to optimize RAM memory.
	 *
	m_subs += m_bus.subscribe<TogglePanelEvent>([&](const TogglePanelEvent& e) {
		if (auto* desc = m_panelManager.getPanel(e.id) {
			if (!m_panelManager.hasPanel(e.id)) {
				m_panelManager.registerPanel(desc->create(m_bus), true); // show
			} else {
				m_panelManager.removePanel(e.id);
			}
		}
	});
	*/
}

void PanelHostLayer::onAttach() {
	AIECAD_CORE_INFO("PanelHostLayer attached, registering panels");

	m_panelManager.registerPanel(
		std::make_unique<DeviceConnectionPanel>(m_bus)
	);

	m_panelManager.registerPanel(
		std::make_unique<ProjectExplorer>(m_bus)
	);

}

void PanelHostLayer::onImGuiRender() {
	m_panelManager.renderVisiblePanels();
}

} // namespace aiecad