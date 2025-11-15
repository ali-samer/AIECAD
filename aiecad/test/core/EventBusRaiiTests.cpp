#include <aiecad/portability/GTest.hpp>

#include <aiecad/core/events/Events.hpp>
#include <aiecad/core/events/EventBus.hpp>
#include <aiecad/core/events/EventSubscription.hpp>

using namespace aiecad;

TEST(EventBusRaii, ListenerIsActiveWhileSubscriptionLives) {
	EventBus bus;

	int callCount {0};
	{
		EventSubscription sub = bus.subscribe<MessageEvent>(
			[&callCount](const MessageEvent& event) {
				++callCount;
				EXPECT_EQ(event.text, "ping");
			}
		);
		EXPECT_TRUE(sub.isValid());

		bus.publish<MessageEvent>(MessageEvent{"ping"});
		EXPECT_EQ(callCount, 1);

		bus.publish<MessageEvent>(MessageEvent{"ping"});
		EXPECT_EQ(callCount, 2);
	}

	bus.publish<MessageEvent>(MessageEvent{"ping"});
	EXPECT_EQ(callCount, 2); // no more calls
}

TEST(EventBusRaii, ResetExplicitlyUnsubscribers) {
	EventBus bus;

	int callCount {0};

	EventSubscription sub = bus.subscribe<MessageEvent>(
		[&callCount](const MessageEvent& event) {
			++callCount;
		}
	);

	bus.publish<MessageEvent>(MessageEvent{"first call"});
	EXPECT_EQ(callCount, 1);

	sub.reset(); // explicit unsubscribe

	EXPECT_FALSE(sub.isValid());

	bus.publish<MessageEvent>(MessageEvent{"second call"});
	EXPECT_EQ(callCount, 1);
}

TEST(EventBusRaii, MoveTransfersOwnership) {
	EventBus bus;

	int callCount {0};

	EventSubscription originalSub = bus.subscribe<MessageEvent>(
		[&callCount](const MessageEvent& event) {
			++callCount;
		}
	);
	EXPECT_TRUE(originalSub.isValid());

	EventSubscription newSub = std::move(originalSub);

	EXPECT_TRUE(newSub.isValid());
	EXPECT_FALSE(originalSub.isValid());

	bus.publish<MessageEvent>(MessageEvent{"Message to newSub"});
	EXPECT_EQ(callCount, 1);
}