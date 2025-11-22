#include <aiecad/ui/UIStyle.hpp>

namespace aiecad {
/*
 * Dark style from:
 * https://github.com/ocornut/imgui/issues/707#issuecomment-2732535348
 */
void UIStyle::ApplyDarkTheme() {
	ImGuiStyle *style  = &ImGui::GetStyle();
	ImVec4 *    colors = style->Colors;

	// Base colors for a pleasant and modern dark theme with dark accents
	colors[ ImGuiCol_Text ] = ImVec4(0.92f, 0.93f, 0.94f, 1.00f); // Light grey text for readability
	colors[ ImGuiCol_TextDisabled ] = ImVec4(0.50f, 0.52f, 0.54f, 1.00f); // Subtle grey for disabled text
	colors[ ImGuiCol_WindowBg ] = ImVec4(0.14f, 0.14f, 0.16f, 1.00f); // Dark background with a hint of blue
	colors[ ImGuiCol_ChildBg ] = ImVec4(0.16f, 0.16f, 0.18f, 1.00f); // Slightly lighter for child elements
	colors[ ImGuiCol_PopupBg ] = ImVec4(0.18f, 0.18f, 0.20f, 1.00f); // Popup background
	colors[ ImGuiCol_Border ] = ImVec4(0.28f, 0.29f, 0.30f, 0.60f); // Soft border color
	colors[ ImGuiCol_BorderShadow ] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f); // No border shadow
	colors[ ImGuiCol_FrameBg ] = ImVec4(0.20f, 0.22f, 0.24f, 1.00f); // Frame background
	colors[ ImGuiCol_FrameBgHovered ] = ImVec4(0.22f, 0.24f, 0.26f, 1.00f); // Frame hover effect
	colors[ ImGuiCol_FrameBgActive ] = ImVec4(0.24f, 0.26f, 0.28f, 1.00f); // Active frame background
	colors[ ImGuiCol_TitleBg ] = ImVec4(0.14f, 0.14f, 0.16f, 1.00f); // Title background
	colors[ ImGuiCol_TitleBgActive ] = ImVec4(0.16f, 0.16f, 0.18f, 1.00f); // Active title background
	colors[ ImGuiCol_TitleBgCollapsed ] = ImVec4(0.14f, 0.14f, 0.16f, 1.00f); // Collapsed title background
	colors[ ImGuiCol_MenuBarBg ] = ImVec4(0.20f, 0.20f, 0.22f, 1.00f); // Menu bar background
	colors[ ImGuiCol_ScrollbarBg ] = ImVec4(0.16f, 0.16f, 0.18f, 1.00f); // Scrollbar background
	colors[ ImGuiCol_ScrollbarGrab ] = ImVec4(0.24f, 0.26f, 0.28f, 1.00f); // Dark accent for scrollbar grab
	colors[ ImGuiCol_ScrollbarGrabHovered ] = ImVec4(0.28f, 0.30f, 0.32f, 1.00f); // Scrollbar grab hover
	colors[ ImGuiCol_ScrollbarGrabActive ] = ImVec4(0.32f, 0.34f, 0.36f, 1.00f); // Scrollbar grab active
	colors[ ImGuiCol_CheckMark ] = ImVec4(0.46f, 0.56f, 0.66f, 1.00f); // Dark blue checkmark
	colors[ ImGuiCol_SliderGrab ] = ImVec4(0.36f, 0.46f, 0.56f, 1.00f); // Dark blue slider grab
	colors[ ImGuiCol_SliderGrabActive ] = ImVec4(0.40f, 0.50f, 0.60f, 1.00f); // Active slider grab
	colors[ ImGuiCol_Button ] = ImVec4(0.24f, 0.34f, 0.44f, 1.00f); // Dark blue button
	colors[ ImGuiCol_ButtonHovered ] = ImVec4(0.28f, 0.38f, 0.48f, 1.00f); // Button hover effect
	colors[ ImGuiCol_ButtonActive ] = ImVec4(0.32f, 0.42f, 0.52f, 1.00f); // Active button
	colors[ ImGuiCol_Header ] = ImVec4(0.24f, 0.34f, 0.44f, 1.00f); // Header color similar to button
	colors[ ImGuiCol_HeaderHovered ] = ImVec4(0.28f, 0.38f, 0.48f, 1.00f); // Header hover effect
	colors[ ImGuiCol_HeaderActive ] = ImVec4(0.32f, 0.42f, 0.52f, 1.00f); // Active header
	colors[ ImGuiCol_Separator ] = ImVec4(0.28f, 0.29f, 0.30f, 1.00f); // Separator color
	colors[ ImGuiCol_SeparatorHovered ] = ImVec4(0.46f, 0.56f, 0.66f, 1.00f); // Hover effect for separator
	colors[ ImGuiCol_SeparatorActive ] = ImVec4(0.46f, 0.56f, 0.66f, 1.00f); // Active separator
	colors[ ImGuiCol_ResizeGrip ] = ImVec4(0.36f, 0.46f, 0.56f, 1.00f); // Resize grip
	colors[ ImGuiCol_ResizeGripHovered ] = ImVec4(0.40f, 0.50f, 0.60f, 1.00f); // Hover effect for resize grip
	colors[ ImGuiCol_ResizeGripActive ] = ImVec4(0.44f, 0.54f, 0.64f, 1.00f); // Active resize grip
	colors[ ImGuiCol_Tab ] = ImVec4(0.20f, 0.22f, 0.24f, 1.00f); // Inactive tab
	colors[ ImGuiCol_TabHovered ] = ImVec4(0.28f, 0.38f, 0.48f, 1.00f); // Hover effect for tab
	colors[ ImGuiCol_TabActive ] = ImVec4(0.24f, 0.34f, 0.44f, 1.00f); // Active tab color
	colors[ ImGuiCol_TabUnfocused ] = ImVec4(0.20f, 0.22f, 0.24f, 1.00f); // Unfocused tab
	colors[ ImGuiCol_TabUnfocusedActive ] = ImVec4(0.24f, 0.34f, 0.44f, 1.00f); // Active but unfocused tab
	colors[ ImGuiCol_PlotLines ] = ImVec4(0.46f, 0.56f, 0.66f, 1.00f); // Plot lines
	colors[ ImGuiCol_PlotLinesHovered ] = ImVec4(0.46f, 0.56f, 0.66f, 1.00f); // Hover effect for plot lines
	colors[ ImGuiCol_PlotHistogram ] = ImVec4(0.36f, 0.46f, 0.56f, 1.00f); // Histogram color
	colors[ ImGuiCol_PlotHistogramHovered ] = ImVec4(0.40f, 0.50f, 0.60f, 1.00f); // Hover effect for histogram
	colors[ ImGuiCol_TableHeaderBg ] = ImVec4(0.20f, 0.22f, 0.24f, 1.00f); // Table header background
	colors[ ImGuiCol_TableBorderStrong ] = ImVec4(0.28f, 0.29f, 0.30f, 1.00f); // Strong border for tables
	colors[ ImGuiCol_TableBorderLight ] = ImVec4(0.24f, 0.25f, 0.26f, 1.00f); // Light border for tables
	colors[ ImGuiCol_TableRowBg ] = ImVec4(0.20f, 0.22f, 0.24f, 1.00f); // Table row background
	colors[ ImGuiCol_TableRowBgAlt ] = ImVec4(0.22f, 0.24f, 0.26f, 1.00f); // Alternate row background
	colors[ ImGuiCol_TextSelectedBg ] = ImVec4(0.24f, 0.34f, 0.44f, 0.35f); // Selected text background
	colors[ ImGuiCol_DragDropTarget ] = ImVec4(0.46f, 0.56f, 0.66f, 0.90f); // Drag and drop target
	colors[ ImGuiCol_NavHighlight ] = ImVec4(0.46f, 0.56f, 0.66f, 1.00f); // Navigation highlight
	colors[ ImGuiCol_NavWindowingHighlight ] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f); // Windowing highlight
	colors[ ImGuiCol_NavWindowingDimBg ] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f); // Dim background for windowing
	colors[ ImGuiCol_ModalWindowDimBg ] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f); // Dim background for modal windows

	// Style adjustments
	style->WindowPadding     = ImVec2(8.00f, 8.00f);
	style->FramePadding      = ImVec2(5.00f, 2.00f);
	style->CellPadding       = ImVec2(6.00f, 6.00f);
	style->ItemSpacing       = ImVec2(6.00f, 6.00f);
	style->ItemInnerSpacing  = ImVec2(6.00f, 6.00f);
	style->TouchExtraPadding = ImVec2(0.00f, 0.00f);
	style->IndentSpacing     = 25;
	style->ScrollbarSize     = 11;
	style->GrabMinSize       = 10;
	style->WindowBorderSize  = 1;
	style->ChildBorderSize   = 1;
	style->PopupBorderSize   = 1;
	style->FrameBorderSize   = 1;
	style->TabBorderSize     = 1;
	style->WindowRounding    = 7;
	style->ChildRounding     = 4;
	style->FrameRounding     = 3;
	style->PopupRounding     = 4;
	style->ScrollbarRounding = 9;
	style->GrabRounding      = 3;
	style->LogSliderDeadzone = 4;
	style->TabRounding       = 4;
}

// I don't remember where I got this from.
void UIStyle::ApplyDraculaTheme() {
	ImGuiStyle *style  = &ImGui::GetStyle();
	ImVec4 *    colors = style->Colors;

	colors[ ImGuiCol_Text ]                  = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
	colors[ ImGuiCol_TextDisabled ]          = ImVec4(0.500f, 0.500f, 0.500f, 1.000f);
	colors[ ImGuiCol_WindowBg ]              = ImVec4(0.180f, 0.180f, 0.180f, 1.000f);
	colors[ ImGuiCol_ChildBg ]               = ImVec4(0.280f, 0.280f, 0.280f, 0.000f);
	colors[ ImGuiCol_PopupBg ]               = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
	colors[ ImGuiCol_Border ]                = ImVec4(0.266f, 0.266f, 0.266f, 1.000f);
	colors[ ImGuiCol_BorderShadow ]          = ImVec4(0.000f, 0.000f, 0.000f, 0.000f);
	colors[ ImGuiCol_FrameBg ]               = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
	colors[ ImGuiCol_FrameBgHovered ]        = ImVec4(0.200f, 0.200f, 0.200f, 1.000f);
	colors[ ImGuiCol_FrameBgActive ]         = ImVec4(0.280f, 0.280f, 0.280f, 1.000f);
	colors[ ImGuiCol_TitleBg ]               = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
	colors[ ImGuiCol_TitleBgActive ]         = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
	colors[ ImGuiCol_TitleBgCollapsed ]      = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
	colors[ ImGuiCol_MenuBarBg ]             = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
	colors[ ImGuiCol_ScrollbarBg ]           = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
	colors[ ImGuiCol_ScrollbarGrab ]         = ImVec4(0.277f, 0.277f, 0.277f, 1.000f);
	colors[ ImGuiCol_ScrollbarGrabHovered ]  = ImVec4(0.300f, 0.300f, 0.300f, 1.000f);
	colors[ ImGuiCol_ScrollbarGrabActive ]   = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
	colors[ ImGuiCol_CheckMark ]             = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
	colors[ ImGuiCol_SliderGrab ]            = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
	colors[ ImGuiCol_SliderGrabActive ]      = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
	colors[ ImGuiCol_Button ]                = ImVec4(1.000f, 1.000f, 1.000f, 0.000f);
	colors[ ImGuiCol_ButtonHovered ]         = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
	colors[ ImGuiCol_ButtonActive ]          = ImVec4(1.000f, 1.000f, 1.000f, 0.391f);
	colors[ ImGuiCol_Header ]                = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
	colors[ ImGuiCol_HeaderHovered ]         = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
	colors[ ImGuiCol_HeaderActive ]          = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
	colors[ ImGuiCol_Separator ]             = colors[ ImGuiCol_Border ];
	colors[ ImGuiCol_SeparatorHovered ]      = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
	colors[ ImGuiCol_SeparatorActive ]       = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
	colors[ ImGuiCol_ResizeGrip ]            = ImVec4(1.000f, 1.000f, 1.000f, 0.250f);
	colors[ ImGuiCol_ResizeGripHovered ]     = ImVec4(1.000f, 1.000f, 1.000f, 0.670f);
	colors[ ImGuiCol_ResizeGripActive ]      = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
	colors[ ImGuiCol_Tab ]                   = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
	colors[ ImGuiCol_TabHovered ]            = ImVec4(0.352f, 0.352f, 0.352f, 1.000f);
	colors[ ImGuiCol_TabActive ]             = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
	colors[ ImGuiCol_TabUnfocused ]          = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
	colors[ ImGuiCol_TabUnfocusedActive ]    = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
	colors[ ImGuiCol_DockingPreview ]        = ImVec4(1.000f, 0.391f, 0.000f, 0.781f);
	colors[ ImGuiCol_DockingEmptyBg ]        = ImVec4(0.180f, 0.180f, 0.180f, 1.000f);
	colors[ ImGuiCol_PlotLines ]             = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
	colors[ ImGuiCol_PlotLinesHovered ]      = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
	colors[ ImGuiCol_PlotHistogram ]         = ImVec4(0.586f, 0.586f, 0.586f, 1.000f);
	colors[ ImGuiCol_PlotHistogramHovered ]  = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
	colors[ ImGuiCol_TextSelectedBg ]        = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
	colors[ ImGuiCol_DragDropTarget ]        = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
	colors[ ImGuiCol_NavHighlight ]          = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
	colors[ ImGuiCol_NavWindowingHighlight ] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
	colors[ ImGuiCol_NavWindowingDimBg ]     = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);
	colors[ ImGuiCol_ModalWindowDimBg ]      = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);

	style->ChildRounding     = 4.0f;
	style->FrameBorderSize   = 1.0f;
	style->FrameRounding     = 2.0f;
	style->GrabMinSize       = 7.0f;
	style->PopupRounding     = 2.0f;
	style->ScrollbarRounding = 12.0f;
	style->ScrollbarSize     = 13.0f;
	style->TabBorderSize     = 1.0f;
	style->TabRounding       = 0.0f;
	style->WindowRounding    = 4.0f;
}

void UIStyle::ApplyAIECADTheme() {
	ImGuiStyle& style = ImGui::GetStyle();
	ImVec4* colors    = style.Colors;

	const ImVec4 bg0      = ImVec4(0.10f, 0.11f, 0.13f, 1.0f); // main window background
	const ImVec4 bg1      = ImVec4(0.13f, 0.14f, 0.17f, 1.0f); // child / panels
	const ImVec4 bg2      = ImVec4(0.17f, 0.18f, 0.21f, 1.0f); // frames
	const ImVec4 bgHover  = ImVec4(0.20f, 0.22f, 0.26f, 1.0f);
	const ImVec4 bgActive = ImVec4(0.24f, 0.26f, 0.30f, 1.0f);

	const ImVec4 text      = ImVec4(0.92f, 0.94f, 0.96f, 1.0f);
	const ImVec4 textMuted = ImVec4(0.55f, 0.57f, 0.60f, 1.0f);

	const ImVec4 accent        = ImVec4(0.07f, 0.76f, 0.71f, 1.0f); // teal
	const ImVec4 accentHover   = ImVec4(0.11f, 0.84f, 0.78f, 1.0f);
	const ImVec4 accentActive  = ImVec4(0.02f, 0.62f, 0.63f, 1.0f);
	const ImVec4 accentLowFill = ImVec4(accent.x, accent.y, accent.z, 0.20f);

	colors[ImGuiCol_Text]           = text;
	colors[ImGuiCol_TextDisabled]   = textMuted;
	colors[ImGuiCol_WindowBg]       = bg0;
	colors[ImGuiCol_ChildBg]        = bg1;
	colors[ImGuiCol_PopupBg]        = ImVec4(bg0.x, bg0.y, bg0.z, 0.98f);
	colors[ImGuiCol_Border]         = ImVec4(0.17f, 0.18f, 0.20f, 1.0f);
	colors[ImGuiCol_BorderShadow]   = ImVec4(0, 0, 0, 0);

	colors[ImGuiCol_FrameBg]        = bg2;
	colors[ImGuiCol_FrameBgHovered] = bgHover;
	colors[ImGuiCol_FrameBgActive]  = bgActive;

	colors[ImGuiCol_TitleBg]            = bg0;
	colors[ImGuiCol_TitleBgActive]      = bg1;
	colors[ImGuiCol_TitleBgCollapsed]   = bg0;
	colors[ImGuiCol_MenuBarBg]          = bg1;

	colors[ImGuiCol_ScrollbarBg]        = bg0;
	colors[ImGuiCol_ScrollbarGrab]      = ImVec4(0.28f, 0.30f, 0.34f, 1.0f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.33f, 0.35f, 0.40f, 1.0f);
	colors[ImGuiCol_ScrollbarGrabActive]  = ImVec4(0.40f, 0.42f, 0.47f, 1.0f);

	colors[ImGuiCol_CheckMark]          = accent;
	colors[ImGuiCol_SliderGrab]         = accent;
	colors[ImGuiCol_SliderGrabActive]   = accentActive;

	colors[ImGuiCol_Button]             = bg2;
	colors[ImGuiCol_ButtonHovered]      = bgHover;
	colors[ImGuiCol_ButtonActive]       = bgActive;

	colors[ImGuiCol_Header]             = ImVec4(bg2.x, bg2.y, bg2.z, 0.90f);
	colors[ImGuiCol_HeaderHovered]      = bgHover;
	colors[ImGuiCol_HeaderActive]       = bgActive;

	colors[ImGuiCol_Separator]          = ImVec4(0.22f, 0.24f, 0.27f, 1.0f);
	colors[ImGuiCol_SeparatorHovered]   = accent;
	colors[ImGuiCol_SeparatorActive]    = accentActive;

	colors[ImGuiCol_ResizeGrip]         = ImVec4(0.30f, 0.32f, 0.36f, 0.80f);
	colors[ImGuiCol_ResizeGripHovered]  = accent;
	colors[ImGuiCol_ResizeGripActive]   = accentActive;

	colors[ImGuiCol_Tab]                = ImVec4(bg1.x, bg1.y, bg1.z, 1.0f);
	colors[ImGuiCol_TabHovered]         = ImVec4(bgHover.x, bgHover.y, bgHover.z, 1.0f);
	colors[ImGuiCol_TabActive]          = ImVec4(bg2.x, bg2.y, bg2.z, 1.0f);
	colors[ImGuiCol_TabUnfocused]       = ImVec4(bg1.x, bg1.y, bg1.z, 1.0f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(bg2.x, bg2.y, bg2.z, 1.0f);

	colors[ImGuiCol_DockingPreview]     = accentLowFill;
	colors[ImGuiCol_DockingEmptyBg]     = bg0;

	colors[ImGuiCol_PlotLines]          = accent;
	colors[ImGuiCol_PlotLinesHovered]   = accentHover;
	colors[ImGuiCol_PlotHistogram]      = accent;
	colors[ImGuiCol_PlotHistogramHovered] = accentHover;

	colors[ImGuiCol_TableHeaderBg]      = bg1;
	colors[ImGuiCol_TableBorderStrong]  = ImVec4(0.22f, 0.24f, 0.27f, 1.0f);
	colors[ImGuiCol_TableBorderLight]   = ImVec4(0.18f, 0.20f, 0.23f, 1.0f);
	colors[ImGuiCol_TableRowBg]         = ImVec4(bg1.x, bg1.y, bg1.z, 0.0f);
	colors[ImGuiCol_TableRowBgAlt]      = ImVec4(bg1.x, bg1.y, bg1.z, 0.60f);

	colors[ImGuiCol_TextSelectedBg]     = accentLowFill;
	colors[ImGuiCol_DragDropTarget]     = accentHover;
	colors[ImGuiCol_NavHighlight]       = accent;
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1, 1, 1, 0.80f);
	colors[ImGuiCol_NavWindowingDimBg]  = ImVec4(0, 0, 0, 0.40f);
	colors[ImGuiCol_ModalWindowDimBg]   = ImVec4(0, 0, 0, 0.60f);

	// Layout and rounding settings
	style.WindowPadding     = ImVec2(10.0f, 10.0f);
	style.FramePadding      = ImVec2(8.0f, 4.0f);
	style.CellPadding       = ImVec2(6.0f, 4.0f);
	style.ItemSpacing       = ImVec2(8.0f, 6.0f);
	style.ItemInnerSpacing  = ImVec2(6.0f, 3.0f);
	style.IndentSpacing     = 20.0f;
	style.ScrollbarSize     = 14.0f;
	style.GrabMinSize       = 10.0f;

	style.WindowBorderSize  = 1.0f;
	style.ChildBorderSize   = 1.0f;
	style.PopupBorderSize   = 1.0f;
	style.FrameBorderSize   = 0.0f;
	style.TabBorderSize     = 0.0f;

	style.WindowRounding    = 6.0f;
	style.ChildRounding     = 4.0f;
	style.FrameRounding     = 4.0f;
	style.PopupRounding     = 4.0f;
	style.ScrollbarRounding = 8.0f;
	style.GrabRounding      = 4.0f;
	style.TabRounding       = 5.0f;

	style.WindowTitleAlign           = ImVec2(0.0f, 0.50f); // left-align title
	style.ColorButtonPosition        = ImGuiDir_Right;
	style.WindowMenuButtonPosition   = ImGuiDir_Right;
	style.DisplaySafeAreaPadding     = ImVec2(4.0f, 4.0f);
}

void UIStyle::ConfigureFont(const char* ttfPath, float sizePixels) {
	ImGuiIO& io = ImGui::GetIO();

	// keep default font for icon merging, if you use it
	// io.Fonts->AddFontDefault();

	ImFont* font = io.Fonts->AddFontFromFileTTF(
	    ttfPath,
	    sizePixels,
	    nullptr,
	    nullptr // default glyph ranges
	);

	if (font) {
		io.FontDefault = font;
	} else {
		// Fallback: at least have some font
		if (io.Fonts->Fonts.empty()) {
			io.Fonts->AddFontDefault();
		}
	}
}

} // namespace aiecad
