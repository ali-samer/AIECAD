#include <aiecad/core/Application.hpp>
#include <aiecad/core/logging/Logger.hpp>
#include <aiecad/core/events/Events.hpp>
#include <aiecad/ui/UI.hpp>

namespace aiecad {
Application& Application::Get() {
	AIECAD_ASSERT(s_instance, "Application does not have an instance of Application");
	return *s_instance;
}

Application::Application(const ApplicationSpecification &spec)
	: m_spec(spec)
	  , m_eventBus(std::make_unique<EventBus>())
	  , m_layerStack(std::make_unique<LayerStack>()) {
	if (s_instance != nullptr) {
		AIECAD_CORE_FATAL("Attempted to create another Application instance");
		throw std::runtime_error("Application instance already exists");
	}
	s_instance = this;

	Logger::Init(LoggerConfig{
		.level = LoggerLevel::Info,
		.toFile = {
			/* TODO: Determine where to log application metadata to. */
		},
		.toStderr = false, .toStdout = true
	});
	AIECAD_CORE_INFO("Application created: {}", m_spec.title);

	m_window = Window::Create(m_spec.winspec);
	setupWindowCallbacks();
	init();
}

Application::~Application() {
	shutdown();
	AIECAD_CORE_INFO("Destroying application: {}", m_spec.title);
	s_instance = nullptr;
}

void Application::setupWindowCallbacks() {
	m_window->setCloseCallback([this]() {
		AIECAD_CORE_INFO("Main window requested close");
		close();
	});

	// TODO: requires additional implementation details
	m_window->setResizeCallback([this](auto width, auto height) {
		AIECAD_CORE_INFO("Main window resized to {}x{}", width, height);
	});
}

void Application::init() {
	AIECAD_CORE_INFO("Initializing Application subsystems");
	setupUIFramework();
	pushAllLayers();
}

/*
 * This shutdown method contains fragile teardown / tight coupling.
 * The shutdown order here assumes implicit knowledge, meaning we
 * have to rely on the developers discipline instead of the compiler
 * enforcing correctness.
 */
void Application::shutdown() {
	AIECAD_CORE_INFO("Shutting down Application subsystems");

	// redundant call but just in case :0
	close();

	// don't change order
	m_layerStack.reset();
	m_ui->shutdown();
	m_ui.reset();
	m_eventBus.reset();
	m_window.reset();
}

int Application::run() {
	AIECAD_CORE_INFO("Starting main loop for '{}'", m_spec.title);

	auto ts = Timestep();
	ts.start();
	while (m_running) {
		float dt = ts.getDelta();
		ts.update();
		
		m_ui->beginFrame();
		for (auto &layer : *m_layerStack) {
			layer->onUpdate(dt);
		}
		m_ui->endFrame();

		m_window->onUpdate();
	}

	AIECAD_CORE_INFO("Main loop exited for '{}'", m_spec.title);
	return 0;
}

void Application::pushLayer(LayerPtr layer) {
	m_layerStack->pushLayer(std::move(layer));
}

void Application::pushOverlay(LayerPtr overlay) {
	m_layerStack->pushOverlay(std::move(overlay));
}

void Application::setupUIFramework() {
	m_ui = std::make_unique<ImGuiFramework>(*m_window);
	m_ui->init();
}

void Application::pushAllLayers() {
	// TODO:
	// This is where to instantiate the core UI layers.
	// Example (once concrete layers are in place):
	//
	// pushLayer(std::make_unique<ViewportLayer>(getEventBus(), ...));
	// pushOverlay(std::make_unique<DebugOverlay>(getEventBus(), ...));
}
} // namespace aiecad
