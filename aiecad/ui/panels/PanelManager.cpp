#include <aiecad/ui/panels/PanelManager.hpp>
#include <aiecad/core/logging/Logger.hpp>

#include <cstring>

namespace aiecad {

UIPanel* PanelManager::findPanel(std::string_view id) noexcept {
	for (auto& p : m_panels) {
		if (std::strcmp(p->id(), id.data()) == 0) {
			return p.get();
		}
	}
	return nullptr;
}

const UIPanel* PanelManager::findPanel(std::string_view id) const noexcept {
	for (auto& p : m_panels) {
		if (std::strcmp(p->id(), id.data()) == 0) {
			return p.get();
		}
	}
	return nullptr;
}

void PanelManager::registerPanel(std::unique_ptr<UIPanel> panel) {
	if (!panel) {
		AIECAD_CORE_WARN("PanelManager: attempted to register null panel");
		return;
	}

	const char* id = panel->id();
	if (!id || !*id) {
		AIECAD_CORE_WARN("PanelManager: panel with empty id, skipping");
		return;
	}

	if (hasPanel(id)) {
		AIECAD_CORE_WARN("PanelManager: panel with id '{}' already registered", id);
		return;
	}

	m_panels.emplace_back(std::move(panel));
}

bool PanelManager::hasPanel(std::string_view id) const noexcept {
	return findPanel(id) != nullptr;
}

bool PanelManager::isVisible(std::string_view id) const noexcept {
	if (auto* p = findPanel(id)) {
		return const_cast<UIPanel*>(p)->visible(); // visible() returns non-const bool&
	}
	return false;
}

void PanelManager::setVisible(std::string_view id, bool visible) noexcept {
	if (auto* p = findPanel(id)) {
		p->visible() = visible;
	}
}

void PanelManager::toggle(std::string_view id) noexcept {
	if (auto* p = findPanel(id)) {
		bool& v = p->visible();
		v = !v;
	}
}

void PanelManager::renderVisiblePanels() {
	for (auto& p : m_panels) {
		if (p->visible()) {
			p->onImGuiRender();
		}
	}
}

} // namespace aiecad