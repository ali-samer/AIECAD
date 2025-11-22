#pragma once

/*
 * All styles have been referenced from:
 * https://github.com/ocornut/imgui/issues/707
 */

#include <imgui.h>
#include <aiecad/macros/Macros.hpp>

namespace aiecad {

/* static */
class UIStyle {
public:
	UIStyle() = delete;
	~UIStyle() = delete;

	static void ApplyDarkTheme();
	static void ApplyDraculaTheme();
	static void ApplyAIECADTheme();

	static void ConfigureFont(const char* ttfPath, float sizePixels = 15.0f);
};
} // namespace aiecad

