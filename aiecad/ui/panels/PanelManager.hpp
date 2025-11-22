#pragma once

#include <aiecad/ui/panels/UIPanel.hpp>
#include <aiecad/core/events/EventBus.hpp>
#include <aiecad/macros/Macros.hpp>

#include <memory>
#include <string_view>
#include <vector>

namespace aiecad {

class PanelManager {
public:
	explicit PanelManager(EventBus& bus)
		: m_bus(bus) {}
	~PanelManager() = default;

	AIECAD_DELETE_COPY_AND_MOVE(PanelManager);

	// Takes ownership.
	void registerPanel(std::unique_ptr<UIPanel> panel);

	// Existence / visibility queries.
	bool hasPanel(std::string_view id) const noexcept;
	bool isVisible(std::string_view id) const noexcept;

	// Visibility control.
	void setVisible(std::string_view id, bool visible) noexcept;
	void toggle(std::string_view id) noexcept;

	// Call this each frame from PanelHostLayer.
	void renderVisiblePanels();

	// Expose panels if needed later.
	const std::vector<std::unique_ptr<UIPanel>>& panels() const noexcept {
		return m_panels;
	}

	int contains(std::string_view id) const noexcept {
		return std::find_if(m_panels.begin(), m_panels.end(), [id](const auto& panel) {
			return panel->id() == id;
		}) != m_panels.end();
	}

private:
	UIPanel*       findPanel(std::string_view id) noexcept;
	const UIPanel* findPanel(std::string_view id) const noexcept;

private:
	std::vector<std::unique_ptr<UIPanel>> m_panels;
	EventBus& m_bus;
};

} // namespace aiecad