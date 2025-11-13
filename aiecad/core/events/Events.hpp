#pragma once

#include <string>
#include <cstdint>

namespace aiecad {

struct WindowCloseEvent {};
struct WindowResizeEvent {
	std::uint32_t width{0};
	std::uint32_t height{0};
};
struct CounterIncrementEvent {};
struct HelloPrintEvent {};
} // namespace aiecad