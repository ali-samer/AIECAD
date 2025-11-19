#include <aiecad/ui/menu/FileMenuItem.hpp>
#include <imgui.h>

namespace aiecad {

void FileMenuItem::onDrawMenuContents() {
	if (ImGui::MenuItem("Exit", "Ctrl+Q")) {
		m_bus.publish(AppShutdownEvent{});
	}

	// TODO: Later – "Open Project", "Save", "Recent Projects", etc...
}

} // namespace aiecad