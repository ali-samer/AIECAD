#include <aiecad/ui/MenuBar.hpp>
#include <aiecad/ui/menu/FileMenuItem.hpp>
#include <aiecad/ui/menu/ToolsMenuItem.hpp>
#include <aiecad/core/logging/Logger.hpp>

namespace aiecad {

MenuBar::MenuBar(EventBus& bus, PanelManager& panelManager)
	: Layer("MenuBarLayer")
	, m_bus(bus)
	, m_panelManager(panelManager)
	, m_menuBar(std::make_unique<GlobalMenuBar>()) {}

void MenuBar::onAttach() {
	AIECAD_CORE_INFO("MenuBarLayer attached");

	// TODO: Register additional core menus here...
	// For now, we only added File with an Exit option and a prototyped DeviceConnectionPanel in Tools
	// Later we should add Edit, View, Run, Help, etc...
	m_menuBar->registerItem(std::make_unique<FileMenuItem>(m_bus));
	m_menuBar->registerItem(std::make_unique<ToolsMenuItem>(m_bus, m_panelManager));
}

void MenuBar::onImGuiRender() {
	if (!m_menuBar) {
		return;
	}
	m_menuBar->render();
}

} // namespace aiecad