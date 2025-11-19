#include <aiecad/ui/UiWidgets.hpp>
#include <imgui.h>

namespace aiecad::ui {

void PanelHeader(const char* title) {
	ImGui::SeparatorText(title);
}

void FormRow(const char* label, const std::function<void()>& drawControl) {
	ImGui::TextUnformatted(label);
	ImGui::SameLine();
	ImGui::SetNextItemWidth(-1.0f);
	drawControl();
}

bool PrimaryButton(const char* label) {
	return ImGui::Button(label);
}

} // namespace aiecad::ui