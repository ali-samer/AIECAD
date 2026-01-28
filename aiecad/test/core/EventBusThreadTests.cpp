#include <aiecad/portability/GTest.hpp>

#include <aiecad/core/events/Events.hpp>
#include <aiecad/core/events/EventBus.hpp>
#include <aiecad/core/events/EventSubscription.hpp>

#include <atomic>
#include <thread>
#include <vector>
#include <chrono>

using namespace aiecad;

TEST(EventBusThreaded, MultipleThreadsPublishingSameEvent) {
    EventBus bus;

    std::atomic callCount{0};

    EventSubscription sub = bus.subscribe<MessageEvent>(
        [&callCount](const MessageEvent&) {
            ++callCount;
        }
    );

    const int numThreads = 4;
    const int publishesPerThread = 1000;

    std::vector<std::thread> threads;
    threads.reserve(numThreads);

    for (int t = 0; t < numThreads; ++t) {
        threads.emplace_back([&bus, publishesPerThread]() {
            for (int i = 0; i < publishesPerThread; ++i) {
                bus.publish(MessageEvent{"ping"});
            }
        });
    }

    for (auto& th : threads) {
        th.join();
    }

    EXPECT_EQ(callCount.load(), numThreads * publishesPerThread);
}

TEST(EventBusThreaded, ResetSubscriptionWhilePublishingFromAnotherThread) {
    EventBus bus;

    std::atomic<int> callCount{0};

    EventSubscription sub = bus.subscribe<MessageEvent>(
        [&callCount](const MessageEvent&) {
            ++callCount;
        }
    );

    const int totalPublishes = 2000;

    std::thread publisher([&bus, totalPublishes]() {
        for (int i = 0; i < totalPublishes; ++i) {
            bus.publish(MessageEvent{"ping"});
            std::this_thread::sleep_for(std::chrono::microseconds(50));
        }
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    sub.reset();

    publisher.join();

    int finalCount = callCount.load();

    EXPECT_GT(finalCount, 0);
    EXPECT_LT(finalCount, totalPublishes);
}

TEST(EventBusThreaded, SubscribeWhileAnotherThreadIsPublishing) {
    EventBus bus;

    std::atomic firstCount{0};
    std::atomic secondCount{0};

    EventSubscription sub1 = bus.subscribe<MessageEvent>(
        [&firstCount](const MessageEvent&) {
            ++firstCount;
        }
    );

    const int totalPublishes = 2000;

    std::thread publisher([&bus, totalPublishes]() {
        for (int i = 0; i < totalPublishes; ++i) {
            bus.publish(MessageEvent{"ping"});
            std::this_thread::sleep_for(std::chrono::microseconds(50));
        }
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    EventSubscription sub2 = bus.subscribe<MessageEvent>(
        [&secondCount](const MessageEvent&) {
            ++secondCount;
        }
    );

    publisher.join();

    EXPECT_GT(firstCount.load(), 0);
    EXPECT_GT(secondCount.load(), 0);
}