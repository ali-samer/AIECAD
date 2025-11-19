#include <aiecad/ui/panels/DeviceConnectionPanel.hpp>
#include <aiecad/ui/UiWidgets.hpp>
#include <aiecad/core/events/Events.hpp>

#include <imgui.h>

namespace aiecad {

DeviceConnectionPanel::DeviceConnectionPanel(EventBus& bus)
	: m_visible(false)
	, m_host{}
	, m_port(22)
, m_user{}
, m_connected(false)
, m_status("Not connected")
, m_bus(bus)
{
	m_toggleSubEvent = m_bus.subscribe<TogglePanelEvent>(
		[&](const TogglePanelEvent& event) {
		if (event.id == id()) {
			toggleVisibility();
		}
	});
}

void DeviceConnectionPanel::onImGuiRender() {
	if (!m_visible) {
		return;
	}

	if (!ImGui::Begin(title(), &m_visible)) {
		ImGui::End();
		return;
	}

	ui::PanelHeader("Device Connection");

	ui::FormRow("Host", [&]{
		ImGui::InputText("##host", m_host, sizeof(m_host));
	});

	ui::FormRow("Port", [&]{
		ImGui::InputInt("##port", &m_port);
	});

	ui::FormRow("User", [&]{
		ImGui::InputText("##user", m_user, sizeof(m_user));
	});

	ImGui::Spacing();

	ImGui::TextUnformatted("Status:");
	ImGui::SameLine();
	ImGui::TextUnformatted(m_status.c_str());

	ImGui::Spacing();

	if (!m_connected) {
		if (ui::PrimaryButton("Connect")) {
			// Prototype behavior: just flip the flag and pretend.
			m_connected = true;
			m_status = "Connected (prototype only)";
		}
	} else {
		if (ui::PrimaryButton("Disconnect")) {
			m_connected = false;
			m_status = "Disconnected";
		}
	}

	ImGui::End();
}

} // namespace aiecad