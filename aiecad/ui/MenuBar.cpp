#include <aiecad/ui/MenuBar.hpp>
#include <aiecad/ui/menu/FileMenuItem.hpp>
#include <aiecad/core/logging/Logger.hpp>

namespace aiecad {

MenuBar::MenuBar(EventBus& bus)
	: Layer("MenuBarLayer")
	, m_bus(bus)
	, m_menuBar(std::make_unique<GlobalMenuBar>()) {}

void MenuBar::onAttach() {
	AIECAD_CORE_INFO("MenuBarLayer attached");

	// Register core menus here.
	// For now, we only add File; later we should add View, Help, Tools, etc.
	m_menuBar->registerItem(std::make_unique<FileMenuItem>(m_bus));
}

void MenuBar::onImGuiRender() {
	if (!m_menuBar) {
		return;
	}
	m_menuBar->render();
}

} // namespace aiecad