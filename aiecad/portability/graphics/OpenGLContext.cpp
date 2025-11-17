#include <aiecad/portability/graphics/OpenGLContext.hpp>
#include <aiecad/core/logging/Logger.hpp>

// GLAD must be included before GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace aiecad {

OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
	: m_windowHandle(windowHandle) {
	AIECAD_ASSERT(m_windowHandle, "Window handle is null in OpenGLContext");
}

void OpenGLContext::init() {
	glfwMakeContextCurrent(m_windowHandle);

	int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
	if (!status) {
		AIECAD_CORE_ERROR("Failed to initialize GLAD");
		AIECAD_ASSERT(false, "Failed to initialize GLAD");
	}

	AIECAD_CORE_INFO("OpenGLContext initialized (GLAD loaded successfully)");

	const GLubyte* vendor   = glGetString(GL_VENDOR);
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version  = glGetString(GL_VERSION);

	AIECAD_CORE_INFO("OpenGL Vendor  : {0}", reinterpret_cast<const char*>(vendor));
	AIECAD_CORE_INFO("OpenGL Renderer: {0}", reinterpret_cast<const char*>(renderer));
	AIECAD_CORE_INFO("OpenGL Version : {0}", reinterpret_cast<const char*>(version));
}

void OpenGLContext::swapBuffers() {
	glfwSwapBuffers(m_windowHandle);
}

} // namespace aiecad