#pragma once

#include <aiecad/core/Window.hpp>
#include <aiecad/core/LayerStack.hpp>
#include <aiecad/core/Specifications.hpp>
#include <aiecad/core/events/EventBus.hpp>
#include <aiecad/ui/panels/PanelManager.hpp>
#include <aiecad/ui/UI.hpp>
#include <aiecad/utils/Timestep.hpp>

#include <atomic>
#include <memory>
#include <string>

namespace aiecad {

class Application {
public:
	using LayerPtr = LayerStack::LayerPtr;

	static Application& Get();
	explicit            Application(const ApplicationSpecification &spec);
	~Application();

	int  run();
	void close() { m_running = false; }

	void pushLayer(LayerPtr layer);
	void pushOverlay(LayerPtr overlay);

	LayerStack&                     getLayerStack() { return *m_layerStack; }
	const LayerStack&               getLayerStack() const { return *m_layerStack; }
	EventBus&                       getEventBus() { return *m_eventBus; }
	Window&                         getWindow() { return *m_window; }
	const ApplicationSpecification& getSpecification() const { return m_spec; }

private:
	/* Helper methods */
	void init();
	void shutdown();

	void setupWindowCallbacks();
	void setupEventSubscription();
	void setupUIFramework();
	void pushAllLayers();

	/* Member variables */
	ApplicationSpecification    m_spec;
	std::unique_ptr<EventBus>   m_eventBus;
	std::unique_ptr<LayerStack> m_layerStack;
	std::unique_ptr<Window>     m_window;
	std::unique_ptr<ImGuiFramework> m_ui;
	std::unique_ptr<PanelManager> m_panelManager;

	EventSubscription m_appShutdownSub;
	std::atomic<bool> m_running{ true };

	static inline Application *s_instance{ nullptr };
};
} // namespace aiecad
