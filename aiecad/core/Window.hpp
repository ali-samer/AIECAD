#pragma once

#include <aiecad/core/Specifications.hpp> // WindowSpecification

#include <functional>
#include <memory>
#include <cstdint>

namespace aiecad {

enum class BackendWindowEventType {
	NONE = 0,
	CLOSE,
	RESIZE
};

struct BackendWindowEvent {
	BackendWindowEventType type {BackendWindowEventType::NONE};
	std::uint32_t width {0};
	std::uint32_t height {0};
};

class Window {
public:
	virtual ~Window() = default;

	// using EventCallbackFn = std::function<void(const BackendWindowEvent&)>;
	virtual void onUpdate() = 0;

	virtual std::uint32_t getWidth() const = 0;
	virtual std::uint32_t getHeight() const = 0;
	virtual void* getNativeHandle() const = 0;

	// virtual void setEventCallback(const EventCallbackFn& /* callback */) = 0;

	virtual void setVSync(bool /* enabled */) = 0;
	virtual bool isVSync() const = 0;
	virtual const std::string& getTitle() const = 0;

	static std::unique_ptr<Window> Create(const WindowSpecification& /* spec */);
};
} // namespace aiecad