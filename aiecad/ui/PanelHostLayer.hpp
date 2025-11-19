#pragma once

#include <aiecad/core/Layer.hpp>
#include <aiecad/core/events/EventBus.hpp>
#include <aiecad/ui/panels/PanelManager.hpp>

namespace aiecad {

class PanelHostLayer final : public Layer {
public:
	explicit PanelHostLayer(EventBus& bus, PanelManager& manager);
	~PanelHostLayer() override = default;

	void onAttach() override;
	void onDetach() override {}

	void onUpdate(float) override {}
	void onImGuiRender() override;

	PanelManager&       panels()       noexcept { return m_panelManager; }
	const PanelManager& panels() const noexcept { return m_panelManager; }

private:
	PanelManager& m_panelManager;
	EventBus& m_bus;
};

} // namespace aiecad