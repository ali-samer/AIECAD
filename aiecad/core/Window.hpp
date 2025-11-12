#pragma once

#include <aiecad/core/Specifications.hpp>
#include <aiecad/core/GraphicsContext.hpp>
#include <aiecad/macros/Macros.hpp>

#include <functional>
#include <memory>

struct Event;

namespace aiecad {
class Window {
public:
	using EventCallbackFn = std::function<void(Event &)>;
	static std::unique_ptr<Window> Create(const WindowSpecification &);

	virtual ~Window() = default;
	virtual void onUpdate() = 0;
	virtual uint32_t getHeight() const = 0;
	virtual uint32_t getWidth() const = 0;
	virtual void*getNativeHandle() const = 0;
	virtual void setVSync(bool) = 0;
	virtual bool isVSync() const = 0;
	virtual void setEventCallback(const EventCallbackFn &) = 0;

	virtual GraphicsContext* getContext() = 0;
};
}
