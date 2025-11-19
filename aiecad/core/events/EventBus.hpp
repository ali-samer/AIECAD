#pragma once

#include <aiecad/core/events/EventSubscription.hpp>
#include <aiecad/macros/Macros.hpp>

#include <functional>
#include <unordered_map>
#include <vector>
#include <typeindex>
#include <mutex>

namespace aiecad {
class EventBus {
public:
	EventBus()  = default;
	~EventBus() = default;
	AIECAD_DELETE_COPY_AND_MOVE(EventBus);

	template < class EventType >
	using Listener = std::function<void(const EventType &)>;

	using ListenerId = std::size_t;

	template < class EventType >
	EventSubscription subscribe(Listener<EventType> listener);

	template < class EventType >
	void publish(const EventType &event);

	ListenerId getNextListenerId() {
		std::lock_guard lock(m_mutex);
		return ++IdCounter;
	}

private:
	friend class EventSubscription;
	using KeyType        = std::type_index;
	using ErasedListener = std::function<void(const void *)>;

	void unsubscribeInternal(KeyType type, ListenerId id);

	struct ListenerRecord {
		ListenerId     id;
		ErasedListener cb;
	};
	using ListenerList = std::vector<ListenerRecord>;
	ListenerId IdCounter{ 0 };
	std::mutex m_mutex;

	std::unordered_map<KeyType, ListenerList> m_listeners;
};
} // namespace aiecad

#include <aiecad/core/events/EventBus.inl>
