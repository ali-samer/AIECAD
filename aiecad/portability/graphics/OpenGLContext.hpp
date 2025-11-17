#pragma once

#include <aiecad/portability/graphics/GraphicsContext.hpp>

struct GLFWwindow;

namespace aiecad {

class OpenGLContext final : public GraphicsContext {
public:
	explicit OpenGLContext(GLFWwindow* windowHandle);
	~OpenGLContext() override = default;

	void init() override;
	void swapBuffers() override;

private:
	GLFWwindow* m_windowHandle;
};
} // namespace aiecad