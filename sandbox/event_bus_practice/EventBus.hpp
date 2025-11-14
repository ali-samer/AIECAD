#pragma once

#include <functional>
#include <unordered_map>
#include <vector>
#include <typeindex>

namespace aiecad {
class SimpleEventBus {
public:
	template < typename TEvent >
	using Listener = std::function<void(const TEvent&)>;

	template < typename TEvent >
	void subscribe(Listener<TEvent> listener) {
		std::type_index type{typeid(TEvent)};

		// we `erase` the listener so we're able to store them in a single container
		auto erased = [fn = std::move(listener)](const void* payload) {
			fn(*static_cast<const TEvent*>(payload));
		};

		m_listeners[type].emplace_back(std::move(erased));
	}

	template < typename TEvent >
	void publish(TEvent& event) {
		std::type_index type{typeid(TEvent)};
		auto it = m_listeners.find(type);
		if (it == m_listeners.end()) {
			return;
		}

		for (auto cb : it->second) {
			cb(static_cast<const void*>(&event));
		}
	}
private:
	using ErasedListener = std::function<void(const void*)>;
	using ListenerContainer = std::vector<ErasedListener>;
	std::unordered_map<std::type_index, ListenerContainer> m_listeners;
};
}