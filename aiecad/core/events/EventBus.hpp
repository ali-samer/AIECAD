#pragma once

#include <aiecad/core/events/EventSubscription.hpp>
#include <aiecad/macros/Macros.hpp>

#include <functional>
#include <typeindex>
#include <unordered_map>
#include <cstddef>
#include <vector>

#include "Events.hpp"

namespace aiecad {

// Central in-process publish/subscribe hub.
// Usage:
//   struct MyEvent { int value; };
//   EventBus bus;
//   auto sub = bus.subscribe<MyEvent>([](const MyEvent& e) { ... });
//   bus.publish(MyEvent{42});
class EventBus {
public:
	using ListenerId = std::size_t;

	template < class EventType >
	using Listener = std::function<void(const EventType &)>;

	EventBus()  = default;
	~EventBus() = default;
	AIECAD_DISABLE_COPY_ASSIGNMENTS(EventBus)

	template < typename EventType >
	EventSubscription subscribe(Listener<EventType> listener) {
		std::type_index typeIndex{ typeid(EventType) };
		ListenerId      id = nextListenerId();

		auto erased = [fn = std::move(listener)] (const void* payload) {
			fn(*static_cast<const EventType*>(payload));
		};

		auto& vec = m_listeners[typeIndex];
		vec.push_back(ListenerRecord{id, std::move(erased)});
		return {this, typeIndex, id};
	}

	template <typename EventType>
	void unsubscribe(ListenerId id) {
		unsubscribeInternal(std::type_index(typeid(EventType)), id);
	}

	template < typename EventType >
	void publish(const EventType &event) {
		std::type_index type{typeid(EventType)};
		auto it = m_listeners.find(type);
		if (it == m_listeners.end()) {
			return;
		}

		auto listenersCopy = it->second;
		for (const auto &record : listenersCopy) {
			if (record.callback) {
				record.callback(static_cast<const void*>(&event));
			}
		}
	}

private:
	friend class EventSubscription;

	void unsubscribeInternal(std::type_index type, ListenerId id) {
		auto it = m_listeners.find(type);
		if (it == m_listeners.end()) {
			return;
		}

		auto &vec = it->second;
		for (auto it = vec.begin(); it != vec.end(); ++it) {
			if (it->id == id) {
				vec.erase(it);
				break;
			}
		}

		if (vec.empty()) {
			m_listeners.erase(type);
		}
	}

	ListenerId nextListenerId() {
		return ++m_lastId;
	}

private:
	struct ListenerRecord {
		ListenerId                        id;
		std::function<void(const void *)> callback;
	};

	std::unordered_map<std::type_index, std::vector<ListenerRecord>> m_listeners;
	ListenerId                                                       m_lastId{ 0 };
};
}
