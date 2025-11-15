#include <aiecad/core/events/EventSubscription.hpp>
#include <aiecad/core/events/EventBus.hpp>

namespace aiecad {

void EventSubscription::reset() {
	if (m_bus && m_listenerId != 0) {
		m_bus->unsubscribeInternal(m_type, m_listenerId);
		m_bus = nullptr;
		m_listenerId = 0;
	}
}

} // namespace aiecad