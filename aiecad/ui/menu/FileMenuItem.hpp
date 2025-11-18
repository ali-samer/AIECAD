#pragma once

#include <aiecad/ui/menu/GlobalMenuItem.hpp>
#include <aiecad/core/events/EventBus.hpp>
#include <aiecad/core/events/Events.hpp>

namespace aiecad {

class FileMenuItem final : public GlobalMenuItem {
public:
	explicit FileMenuItem(EventBus& bus) noexcept
		: m_bus(bus) {}

	const char* label() const noexcept override {
		return "File";
	}

	void onDrawMenuContents() override;

private:
	EventBus& m_bus; // non-owning
};

} // namespace aiecad