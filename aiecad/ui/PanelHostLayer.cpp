#include <aiecad/ui/PanelHostLayer.hpp>
#include <aiecad/core/logging/Logger.hpp>

#include <aiecad/ui/panels/DeviceConnectionPanel.hpp>

namespace aiecad {

PanelHostLayer::PanelHostLayer(EventBus& bus, PanelManager& manager)
	: Layer("PanelHostLayer")
	, m_bus(bus)
	, m_panelManager(manager) {}

void PanelHostLayer::onAttach() {
	AIECAD_CORE_INFO("PanelHostLayer attached, registering panels");

	m_panelManager.registerPanel(
		std::make_unique<DeviceConnectionPanel>(m_bus)
	);
}

void PanelHostLayer::onImGuiRender() {
	m_panelManager.renderVisiblePanels();
}

} // namespace aiecad