#pragma once

#include <aiecad/ui/menu/GlobalMenuItem.hpp>
#include <aiecad/ui/panels/PanelManager.hpp>
#include <aiecad/core/events/EventBus.hpp>
#include <aiecad/core/events/Events.hpp>

#include <imgui.h>

namespace aiecad {

class ToolsMenuItem final : public GlobalMenuItem {
public:
	explicit ToolsMenuItem(EventBus& bus, PanelManager& panelManager) noexcept
		: m_bus(bus), m_panelManager(panelManager) {}

	const char* label() const noexcept override {
		return "Tools";
	}

	void onDrawMenuContents() override;

private:
	// `populate<T>()` assumes the panel has two static methods:
	// - T::Id();
	// - T::Title();
	//
	// A better approach would be to use an RAII-ish lookup for
	// panels that are registered with the PanelManager.
	// That way each panel gets its own unique identifier and doesn't
	// require this weird integration.
	//
	// This will work for now...
	template < class T >
	requires requires { {T::Id()}; {T::Title()}; }
	void populatePanel() {
		auto id = T::Id();

		auto hasPanel = m_panelManager.hasPanel(id);
		if (!hasPanel) { return; }

		bool visible = m_panelManager.isVisible(id);
		if (ImGui::MenuItem(T::Title(), nullptr, visible)) {
			m_bus.publish(TogglePanelEvent{id});
		}
	}

private:
	EventBus& m_bus;
	PanelManager& m_panelManager;
};
} // namespace aiecad