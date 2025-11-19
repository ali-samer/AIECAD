#pragma once

#include <string_view>

namespace aiecad {

enum class PanelCategory {
	Editor,
	Tool,
	Diagnostic
};

class UIPanel {
public:
	virtual ~UIPanel() = default;

	// Internal id, must be stable (used by PanelManager and persistence).
	virtual const char* id() const noexcept = 0;

	// ImGui window title.
	virtual const char* title() const noexcept = 0;

	// Category for grouping/filtering.
	virtual PanelCategory category() const noexcept = 0;

	// Visibility flag (PanelManager will read/write this).
	virtual bool& visible() noexcept = 0;

	// Draw this panel's ImGui contents.
	virtual void onImGuiRender() = 0;
};

} // namespace aiecad