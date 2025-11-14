#pragma once

#include <string>
#include <cstdint>

namespace aiecad {
struct WindowCloseEventSimple {};
struct WindowResizeEventSimple {
	std::uint32_t width{0};
	std::uint32_t height{0};
};

struct CounterIncrementEventSimple {};
struct MessageEventSimple {
	std::string text;
};
}