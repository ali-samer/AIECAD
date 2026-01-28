#include <aiecad/core/events/EventBus.hpp>

namespace aiecad {

void EventBus::unsubscribeInternal(KeyType key, ListenerId id) {
	auto it = m_listeners.find(key);
	if (it == m_listeners.end()) {
		return;
	}

	auto vec = it->second;
	for (auto it = vec.begin(); it != vec.end(); it++) {
		if (it->id == id) {
			vec.erase(it);
			break;
		}
	}

	if (vec.empty()) {
		m_listeners.erase(key);
	}
}
} // namespace aiecad