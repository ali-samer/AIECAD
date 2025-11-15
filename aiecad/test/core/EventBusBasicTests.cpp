#include <aiecad/portability/GTest.hpp>

#include <aiecad/core/events/Events.hpp>
#include <aiecad/core/events/EventBus.hpp>

using namespace aiecad;

TEST(EventBusBasic, SingleListenerReceivesEvent) {
	EventBus bus;

	bool called{ false };

	auto id = bus.subscribe<MessageEvent>(
		[&called](const MessageEvent &e) {
			called = true;
			EXPECT_EQ(e.text, "hello");
		}
	);
	(void)id;

	bus.publish(MessageEvent{ "hello" });
	EXPECT_TRUE(called);
}

TEST(EventBusBasic, MultipleListenerReceiveEvent) {
	EventBus bus;

	int callCount{ 0 };
	auto id1 = bus.subscribe<MessageEvent>(
		[&callCount](const MessageEvent &e) {
			++callCount;
		}
	);

	auto id2 = bus.subscribe<MessageEvent>(
		[&callCount](const MessageEvent &e) {
			++callCount;
		}
	);
	(void)id1;
	(void)id2;

	EXPECT_EQ(callCount, 0);
	bus.publish(MessageEvent{ "Multi-Listener Test" });
	EXPECT_EQ(callCount, 2);
}

TEST(EventBusBasic, DifferentEventTypesDoNotInterfere) {
	EventBus bus;

	bool gotMsg{ false };
	bool gotCounter{ false };

	auto msgId = bus.subscribe<MessageEvent>(
		[&gotMsg](const MessageEvent &e) {
			gotMsg = true;
		}
	);

	auto counterId = bus.subscribe<CounterIncrementEvent>(
		[&gotCounter](const CounterIncrementEvent &e) {
			gotCounter = true;
		}
	);
	(void)msgId;
	(void)counterId;

	bus.publish(MessageEvent{"msg"});
	EXPECT_TRUE(gotMsg);
	EXPECT_FALSE(gotCounter);

	bus.publish(CounterIncrementEvent{});
	EXPECT_TRUE(gotCounter);
}

TEST(EventBusUnsubscribe, ListenerDoesNotReceiveAfterReset) {
	EventBus bus;

	int callCount = 0;

	EventSubscription sub = bus.subscribe<MessageEvent>(
		[&callCount](const MessageEvent&) {
			++callCount;
		}
	);

	bus.publish(MessageEvent{"first"});
	EXPECT_EQ(callCount, 1);

	sub.reset();

	bus.publish(MessageEvent{"second"});
	EXPECT_EQ(callCount, 1);
}