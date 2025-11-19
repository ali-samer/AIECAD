#pragma once

#include <functional>

namespace aiecad::ui {

void PanelHeader(const char* title);

// Draw a simple form row: label on the left, control on the right.
void FormRow(const char* label, const std::function<void()>& drawControl);

// Primary action button (use your theme later).
bool PrimaryButton(const char* label);

} // namespace aiecad::ui