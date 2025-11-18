#pragma once

#include <memory>

#include <aiecad/core/Layer.hpp>
#include <aiecad/core/events/EventBus.hpp>
#include <aiecad/ui/menu/GlobalMenuBar.hpp>
#include <aiecad/macros/Macros.hpp>

namespace aiecad {

class MenuBar final : public Layer {
public:
	explicit MenuBar(EventBus& bus);
	~MenuBar() override = default;

	AIECAD_DELETE_COPY_AND_MOVE(MenuBar);

	void onAttach() override;
	void onDetach() override {}

	void onUpdate(float) override {}
	void onImGuiRender() override;

	GlobalMenuBar& getMenuBar() { return *m_menuBar; }

private:
	EventBus&                      m_bus;      // non-owning
	std::unique_ptr<GlobalMenuBar> m_menuBar;  // single instance (logical singleton)
};

} // namespace aiecad