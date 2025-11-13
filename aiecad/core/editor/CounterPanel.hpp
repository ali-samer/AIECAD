#pragma once

#include <aiecad/core/events/EventBus.hpp>
#include <aiecad/core/events/Events.hpp>

#include <imgui.h>

namespace aiecad {

struct CounterModel {
	int value {0};
};

class CounterController {
public:
	CounterController(EventBus& bus, CounterModel& model)
		: m_bus(bus)
		, m_model(model) {

		m_incrementSub = m_bus.subscribe<CounterIncrementEvent>(
			[this](const CounterIncrementEvent&) {
				m_model.value++;
			}
		);
	}

private:
	EventBus&         m_bus;
	CounterModel&     m_model;
	EventSubscription m_incrementSub;
};

class CounterView {
public:
	CounterView(EventBus& bus, CounterModel& model)
		: m_bus(bus)
		, m_model(model) {}

	void draw() {
		ImGui::Text("Count: %d", m_model.value);
		if (ImGui::Button("Increment")) {
			m_bus.publish(CounterIncrementEvent{});
		}
	}

private:
	EventBus&     m_bus;
	CounterModel& m_model;
};

class CounterPanel {
public:
	explicit CounterPanel(EventBus& bus)
		: m_model()
		, m_controller(bus, m_model)
		, m_view(bus, m_model) {}

	void onImGuiRender() {
		m_view.draw();
	}

private:
	CounterModel      m_model;
	CounterController m_controller;
	CounterView       m_view;
};

} // namespace aiecad