#pragma once

#include <aiecad/core/Window.hpp>
#include <aiecad/core/Specifications.hpp>

struct GLFWwindow;

namespace aiecad {

class GLFWWindow final : public Window {
public:
	explicit GLFWWindow(const WindowSpecification& spec);
	~GLFWWindow() override;

	void init(const WindowSpecification& spec);
	void shutdown();
	void onUpdate() override;

	unsigned int       getWidth() const override {return m_spec.width; }
	unsigned int       getHeight() const override {return m_spec.height; }
	void*              getNativeHandle() const override { return m_window; }
	const std::string& getTitle() const override { return m_spec.title; }

	void setVSync(bool /* enabled */) override;
	bool isVSync() const override { return m_spec.vsync; }

	static bool validSpec(const WindowSpecification& spec, std::string* err_desc) noexcept;

private:
	GLFWwindow* m_window;
	WindowSpecification m_spec;
};
} // namespace aiecad