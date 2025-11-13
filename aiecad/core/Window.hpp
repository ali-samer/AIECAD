#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <string>

#include <aiecad/core/Specifications.hpp> // WindowSpecification

namespace aiecad {

enum class BackendWindowEventType {
	None = 0,
	Close,
	Resize,
};

struct BackendWindowEvent {
	BackendWindowEventType type {BackendWindowEventType::None};
	std::uint32_t width  {0}; // only meaningful for Resize
	std::uint32_t height {0};
};

class Window {
public:
	using EventCallbackFn = std::function<void(const BackendWindowEvent&)>;

	virtual ~Window() = default;

	virtual void onUpdate() = 0;

	virtual std::uint32_t getWidth() const = 0;
	virtual std::uint32_t getHeight() const = 0;

	virtual void setEventCallback(const EventCallbackFn& callback) = 0;

	virtual void setVSync(bool enabled) = 0;
	virtual bool isVSync() const = 0;

	// For ImGui / renderer backends.
	virtual void* getNativeHandle() const = 0;

	static std::unique_ptr<Window> Create(const WindowSpecification& winSpec);
};

} // namespace aiecad