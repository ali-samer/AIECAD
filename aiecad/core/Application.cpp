#include <aiecad/core/Application.hpp>
#include <aiecad/core/events/EventBus.hpp>
#include <aiecad/core/Window.hpp>
#include <aiecad/core/logging/Logger.hpp>

#include <aiecad/core/editor/EditorLayer.hpp>
#include <aiecad/core/editor/EmptyLayer.hpp>

#include "imgui.h"
#include <imgui_internal.h>

// FIXME: `aiecad_lib` target should see those
#include "Release/bindings/imgui_impl_glfw.h"
#include "Release/bindings/imgui_impl_opengl3.h"

namespace aiecad {
Application *Application::s_instance{ nullptr };

Application& Application::Get() {
	if (not s_instance) {
		AIECAD_CORE_FATAL("Application::Get() called before instance exists");
		throw std::runtime_error("No Application instance");
	}
	return *s_instance;
}

Application::Application(const ApplicationSpecification &app_spec)
	: m_appSpec(app_spec) {
	if (s_instance) {
		AIECAD_CORE_FATAL("Attempted to create another `Application` instance while one already exists");
		throw std::runtime_error("Application instance already exists");
	}

	Logger::Init({
		.level = LoggerLevel::Debug,
		.toFile = { /* TODO: Determine where to log behavior to. */},
		.toStdout = true, .toStderr = false,
	});
	s_instance = this;
	AIECAD_CORE_INFO("Initializing application");
	init();
	AIECAD_CORE_INFO("Application initialized");
}

Application::~Application() {
	shutdown();
	s_instance = nullptr;
}

/*
void Application::init() {
	m_eventBus = std::make_unique<EventBus>();
	m_window   = Window::Create(m_appSpec.window_spec);

	m_window->setEventCallback(
		[this](const BackendWindowEvent& e) {
			switch (e.type) {
			case BackendWindowEventType::Close:
					m_eventBus->publish(WindowCloseEvent{});
					break;
				case BackendWindowEventType::Resize:
					m_eventBus->publish(WindowResizeEvent{
						.width  = e.width,
						.height = e.height
					});
					break;
				default:
					break;
				}
			}
		);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)m_window->getNativeHandle(), true);
	ImGui_ImplOpenGL3_Init("#version 450");

	auto editorLayer = std::make_unique<EditorLayer>(*m_eventBus);
	pushLayer(std::move(editorLayer));
	pushLayer(std::make_unique<EmptyLayer>());

	m_eventBus->subscribe<WindowCloseEvent>(
		[this](const WindowCloseEvent&) {
			requestClose();
		}
	);
}
*/

void Application::init() {
	m_eventBus = std::make_unique<EventBus>();

	WindowSpecification windowSpec{};
	windowSpec.title     = m_appSpec.name;
	windowSpec.width     = m_appSpec.window_spec.width;
	windowSpec.height    = m_appSpec.window_spec.height;
	windowSpec.vSync     = m_appSpec.window_spec.vSync;

	m_window = Window::Create(windowSpec);
    AIECAD_CORE_INFO("Window created");

	m_window->setEventCallback(
		[this](const BackendWindowEvent& e) {
			if (e.type == BackendWindowEventType::Close) {
				AIECAD_CORE_INFO("[BackendWindowEventType] Closing application");
				m_eventBus->publish(WindowCloseEvent{});
			}
		}
	);

	m_windowCloseSub = m_eventBus->subscribe<WindowCloseEvent>(
		[this](const WindowCloseEvent&) {
			AIECAD_CORE_INFO("[WindowCloseEvent] Closing application");
			requestClose();
		}
	);
}

void Application::shutdown() {
	m_window.reset();
	m_eventBus.reset();
}

/*
int Application::run() {
	m_timestep.start();

	while (m_running) {
		m_window->onUpdate();

		float dt = m_timestep.getDelta();
		m_timestep.update();

		for (auto &layerPtr : m_layerStack.getLayers()) {
			if (layerPtr) {
				layerPtr->onUpdate(dt);
			}
		}

		for (auto &layerPtr : m_layerStack.getLayers()) {
			if (layerPtr) {
				layerPtr->onImGuiRender();
			}
		}

	}
	return 0;
}
 */

int Application::run() {
	while (m_running) {
		if (m_window) {
			m_window->onUpdate();  // polls events + swaps buffers
		} else {
			break;
		}
	}
	return 0;
}

void Application::pushLayer(LayerPtr layer) {
	m_layerStack.pushLayer(std::move(layer));
}

void Application::pushOverlay(LayerPtr overlay) {
	m_layerStack.pushOverlay(std::move(overlay));
}
} // namespace aiecad
