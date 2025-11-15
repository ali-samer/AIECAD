#pragma once

#include <cstddef>
#include <typeindex>

namespace aiecad {
class EventBus;

/*
 * RAII handle for a single subscription.
 * Keep in mind, the object automatically unsubscribes once it's destroyed.
 */
class EventSubscription {
public:
	EventSubscription() = default;

	// tightly coupling types from EventBus is intentional since
	EventSubscription(EventBus *eventBus, std::type_index type, std::size_t id) noexcept
		: m_bus(eventBus), m_type(type), m_id(id) {
	}

	~EventSubscription() {
		reset();
	}

	EventSubscription(EventSubscription &&other) noexcept
		: m_bus(other.m_bus), m_type(other.m_type), m_id(other.m_id) {
		other.m_bus = nullptr;
		other.m_id  = 0;
	}

	EventSubscription(const EventSubscription &other)            = delete;
	EventSubscription& operator=(const EventSubscription &other) = delete;
	EventSubscription& operator=(EventSubscription &&other) noexcept {
		if (this != &other) {
			reset();
			m_bus       = other.m_bus;
			m_type      = other.m_type;
			m_id        = other.m_id;
			other.m_bus = nullptr;
			other.m_id  = 0;
		}
		return *this;
	}

	bool isValid() const {
		return m_bus != nullptr && m_id != 0;
	}

	void reset();

	explicit operator bool() const noexcept { return isValid(); }

private:
	EventBus *      m_bus{ nullptr };
	std::type_index m_type{ typeid(void) };
	std::size_t     m_id{ 0 };
};
} // namespace aiecad