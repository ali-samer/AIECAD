#pragma once

#include <aiecad/core/Window.hpp>
#include <aiecad/core/Specifications.hpp>
#include <aiecad/portability/graphics/GraphicsContext.hpp>

#include <memory>

struct GLFWwindow;

namespace aiecad {
class GLFWWindow final : public Window {
public:
	explicit GLFWWindow(const WindowSpecification &spec);
	~GLFWWindow() override;

	void init(const WindowSpecification &spec);
	void shutdown();
	void onUpdate() override;

	std::uint32_t      getWidth() const override { return m_spec.width; }
	std::uint32_t      getHeight() const override { return m_spec.height; }
	void*              getNativeHandle() const override { return m_window; }
	const std::string& getTitle() const override { return m_spec.title; }

	void setupCallbacks();
	void setCloseCallback(CloseCallback cb) override { m_closeCallback = std::move(cb); }
	void setResizeCallback(ResizeCallback cb) override { m_resizeCallback = std::move(cb); }

	void setVSync(bool /* enabled */) override;
	bool isVSync() const override { return m_spec.vsync; }

	static bool validSpec(const WindowSpecification &spec, std::string *err_desc) noexcept;

private:
	GLFWwindow *                     m_window;
	std::unique_ptr<GraphicsContext> m_context;
	WindowSpecification              m_spec;

	CloseCallback  m_closeCallback;
	ResizeCallback m_resizeCallback;
};
} // namespace aiecad
