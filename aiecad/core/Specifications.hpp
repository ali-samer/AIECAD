#pragma once

#include <aiecad/core/logging/LoggerConfig.hpp>

#include <string>
#include <cstdint>

namespace aiecad {
struct WindowSpecification {
	std::string   title;
	std::uint32_t width{ 900 };
	std::uint32_t height{ 900 };
	bool          vsync{ true };
	bool          resizable{ true };
};

struct ApplicationSpecification {
	std::string   title {"AIECAD"};
	WindowSpecification winspec;
	LoggerConfig logspec;
};
} // namespace aiecad
