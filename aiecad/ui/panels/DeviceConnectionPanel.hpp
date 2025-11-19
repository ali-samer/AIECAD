#pragma once

#include <aiecad/ui/panels/UIPanel.hpp>
#include <aiecad/core/events/EventSubscription.hpp>
#include <aiecad/core/events/EventBus.hpp>

#include <string>

namespace aiecad {

class DeviceConnectionPanel final : public UIPanel {
public:
	explicit DeviceConnectionPanel(EventBus& bus);

	static constexpr const char* Id()    noexcept { return "device_connection"; }
	static constexpr const char* Title() noexcept { return "Device Connection"; }

	const char* id() const noexcept override    { return Id(); }
	const char* title() const noexcept override { return Title(); }
	PanelCategory category() const noexcept override { return PanelCategory::Tool; }

	bool& visible() noexcept override { return m_visible; }
	void toggleVisibility() noexcept { m_visible = !m_visible; }

	void onImGuiRender() override;

private:
	bool m_visible{false};

	// Prototype state (UI only for now)
	char m_host[128];
	int  m_port;
	char m_user[64];

	bool        m_connected{false};
	std::string m_status;

	EventBus& m_bus;
	EventSubscription m_toggleSubEvent;
};

} // namespace aiecad