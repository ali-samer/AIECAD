#pragma once

#include <aiecad/core/events/EventSubscription.hpp>
#include <aiecad/macros/Macros.hpp>

#include <vector>

namespace aiecad {
class EventSubscriptionGroup {
public:
	using Container = std::vector<EventSubscription>;

	EventSubscriptionGroup()  = default;
	~EventSubscriptionGroup() = default; // cpp std ensures EventSubscription dtor is called when main dtor is called

	AIECAD_DELETE_COPY_AND_MOVE(EventSubscriptionGroup);

	void  operator +=(EventSubscription &&sub) { m_subscriptions.emplace_back(std::move(sub)); }
	auto& operator [](int i) { return get(i); }

	void  clear() noexcept { m_subscriptions.clear(); }
	int   size() const noexcept { return static_cast<int>(m_subscriptions.size()); }
	auto& get(int index) { return m_subscriptions.at(index); }

private:
	Container m_subscriptions;
};
} // namespace aiecad
