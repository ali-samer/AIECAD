#pragma once

#include <string>
#include <memory>

#include <aiecad/core/Window.hpp>

struct GLFWwindow;
namespace aiecad {

class GLFWWindow final : public Window {
public:
	explicit GLFWWindow(const WindowSpecification& spec);
	~GLFWWindow() override;

	void onUpdate() override;

	std::uint32_t getWidth() const override { return m_data.width; }
	std::uint32_t getHeight() const override { return m_data.height; }

	void setEventCallback(const EventCallbackFn& callback) override {
		m_data.eventCallback = callback;
	}

	void setVSync(bool enabled) override;
	bool isVSync() const override { return m_data.vsync; }

	void* getNativeHandle() const override { return m_window; }

private:
	void init(const WindowSpecification& spec);
	void shutdown();

private:
	GLFWwindow* m_window {nullptr};

	struct WindowData {
		std::string     title {"AIECAD"}; // Set by `init`
		std::uint32_t   width {1280};
		std::uint32_t   height{720};
		bool            vsync {true};
		EventCallbackFn eventCallback;
	};

	WindowSpecification m_winSpec{};
	WindowData m_data;
};

} // namespace aiecad