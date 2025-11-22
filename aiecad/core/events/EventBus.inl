#pragma once

#include <typeindex>
namespace aiecad {

template < class EventType >
EventSubscription EventBus::subscribe(Listener<EventType> listener) {
	KeyType type{typeid(EventType)};
	ListenerId id = getNextListenerId();

	auto erased = [fn = std::move(listener)](const void* payload) {
		const EventType& event = *static_cast<const EventType*>(payload);
		fn(event);
	};

	{
		std::lock_guard lock(m_mutex);
		auto& vec = m_listeners[type];
		vec.push_back(ListenerRecord{id, std::move(erased)});
	}

	return {this, type, id};
}

template < class EventType >
void EventBus::publish(const EventType& event) {
	KeyType type{typeid(EventType)};

	ListenerList listenersCopy;

	{
		std::lock_guard lock(m_mutex);
		auto it = m_listeners.find(type);
		if (it == m_listeners.end()) {
			return;
		}
		listenersCopy = it->second;
	}

	for (auto& record : listenersCopy) {
		record.cb(static_cast<const void*>(&event));
	}
}
}
