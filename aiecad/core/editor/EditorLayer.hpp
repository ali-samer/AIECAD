#pragma once

#include <memory>

#include <aiecad/core/Layer.hpp>
#include <aiecad/core/events/EventBus.hpp>
#include <aiecad/core/editor/CounterPanel.hpp>

namespace aiecad {

class EditorLayer : public Layer {
public:
	explicit EditorLayer(EventBus& bus)
		: Layer("EditorLayer")
		, m_eventBus(bus) {}

	void onAttach() override;
	void onDetach() override;
	void onUpdate(float /*dt*/) override {}
	void onImGuiRender() override;

private:
	EventBus& m_eventBus;

	std::unique_ptr<CounterPanel> m_counterPanel;
	// later: std::unique_ptr<HelloPanel> m_helloPanel;
};

} // namespace aiecad