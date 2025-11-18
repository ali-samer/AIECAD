#include <aiecad/ui/menu/GlobalMenuBar.hpp>
#include <aiecad/core/logging/Logger.hpp>

#include <imgui.h>

namespace aiecad {

void GlobalMenuBar::registerItem(std::unique_ptr<GlobalMenuItem> item) {
	if (!item) {
		AIECAD_CORE_WARN("Attempted to register a null GlobalMenuItem");
		return;
	}
	m_items.emplace_back(std::move(item));
}

void GlobalMenuBar::render() {
	if (m_items.empty()) {
		return; // nothing to draw
	}

	if (!ImGui::BeginMainMenuBar()) {
		return;
	}

	for (auto& item : m_items) {
		const char* label = item->label();
		if (!label || !*label) {
			continue;
		}

		if (ImGui::BeginMenu(label)) {
			item->onDrawMenuContents();
			ImGui::EndMenu();
		}
	}

	ImGui::EndMainMenuBar();
}

} // namespace aiecad