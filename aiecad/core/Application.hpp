#pragma once

#include <aiecad/core/LayerStack.hpp>
#include <aiecad/core/Specifications.hpp>
#include <aiecad/utils/Timestep.hpp>
#include <aiecad/core/events/EventSubscription.hpp>

namespace aiecad {
class EventBus;
class Window;

class Application {
public:
	static Application& Get();

	explicit Application(const ApplicationSpecification &app_spec);
	~Application();

	// main loop entry point
	int  run();
	void requestClose() { m_running = false; }
	void pushLayer(LayerPtr layer);
	void pushOverlay(LayerPtr overlay);

	// accessors.
	LayerStack&                     getLayerStack() { return m_layerStack; }
	const LayerStack&               getLayerStack() const { return m_layerStack; }
	EventBus&                       getEventBus() { return *m_eventBus; }
	Window&                         getWindow() { return *m_window; }
	const ApplicationSpecification& getSpecification() const { return m_appSpec; }

private:
	void init();
	void shutdown();
	void setupUIFramework();
	void pushLayers();

private:
	ApplicationSpecification  m_appSpec;
	LayerStack                m_layerStack;
	std::unique_ptr<EventBus> m_eventBus;
	std::unique_ptr<Window>   m_window;
	std::atomic<bool>         m_running{ true };
	Timestep                  m_timestep;
	EventSubscription         m_windowCloseSub;

	static Application *s_instance;
};
} // namespace aiecad
