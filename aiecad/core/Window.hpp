#pragma once

#include <aiecad/core/Specifications.hpp> // WindowSpecification

#include <functional>
#include <memory>
#include <cstdint>

#include "aiecad/macros/internal/ObjectTraits.hpp"

namespace aiecad {

class Window {
public:
	using CloseCallback = std::function<void()>;
	using ResizeCallback = std::function<void(std::uint32_t, std::uint32_t)>;

	virtual ~Window() = default;
	AIECAD_DELETE_COPY_AND_MOVE(Window);

	virtual void onUpdate() = 0;

	virtual std::uint32_t getWidth() const = 0;
	virtual std::uint32_t getHeight() const = 0;
	virtual void* getNativeHandle() const = 0;

	virtual void setCloseCallback(CloseCallback cb) = 0;
	virtual void setResizeCallback(ResizeCallback cb) = 0;

	virtual void setVSync(bool /* enabled */) = 0;
	virtual bool isVSync() const = 0;
	virtual const std::string& getTitle() const = 0;

	static std::unique_ptr<Window> Create(const WindowSpecification& /* spec */);

protected:
	Window() = default;
};
} // namespace aiecad