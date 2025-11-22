#include <aiecad/core/events/EventBus.hpp>

#include <algorithm>

namespace aiecad {

void EventBus::unsubscribeInternal(KeyType key, ListenerId id) {
	std::lock_guard lock(m_mutex);
	auto it = m_listeners.find(key);
	if (it == m_listeners.end()) {
		return;
	}

	auto &vec = it->second;
	vec.erase(std::remove_if(vec.begin(), vec.end(),
		[id](const ListenerRecord &record) { return record.id == id; }),
		vec.end());

	if (vec.empty()) {
		m_listeners.erase(it);
	}
}
} // namespace aiecad
