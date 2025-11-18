#pragma once

namespace aiecad {

class GlobalMenuItem {
public:
	virtual ~GlobalMenuItem() = default;

	virtual const char* label() const noexcept = 0;

	// Called when ImGui has begun this menu.
	// Implementations should draw their sub-items here.
	virtual void onDrawMenuContents() = 0;
};

} // namespace aiecad