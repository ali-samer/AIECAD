#pragma once

#include <string>
#include <cstdint>
#include <filesystem>
namespace fs = std::filesystem;

namespace aiecad {
struct WindowSpecification;
struct ApplicationSpecification;

struct WindowSpecification {
	std::string   title;
	uint32_t      width;
	uint32_t      height;
	bool          resizable;
	bool          vSync;
	float         dpiScale;
	std::uint32_t specVersion; // maybe not needed
};

struct ApplicationSpecification {
	std::string name{ "AIECAD" };
	fs::path    sandboxRoot{ };
	bool        devMode{ false };
	bool        maximized{ false };

	WindowSpecification window_spec{
		.title = name, .width = 1600, .height = 900,
		.resizable = true, .vSync = true, .dpiScale = 1.f,
	};
};
} // namespace aiecad
