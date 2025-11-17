#pragma once

#include <string>
#include <cstdint>

namespace aiecad {

struct WindowCloseEvent {};
struct WindowResizeEvent {
	std::uint32_t width{0};
	std::uint32_t height{0};
};

// TODO: These are temporary events, made to test out the EventBus API. Must be removed.
struct CounterIncrementEvent {};
struct HelloPrintEvent {};
struct MessageEvent {
	std::string text;
};

struct AppShutdownEvent {};
} // namespace aiecad