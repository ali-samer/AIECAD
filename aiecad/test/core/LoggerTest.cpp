#include <aiecad/portability/GTest.hpp>

#include <aiecad/core/logging/Logger.hpp>
#include <aiecad/core/logging/LoggerConfig.hpp>

#include <atomic>
#include <thread>
#include <vector>

using aiecad::Logger;
using aiecad::LoggerConfig;

TEST(LoggerTest, MultiThreadedInitAndLoggingIsSafe) {
    EXPECT_FALSE(Logger::IsInitialized());

    LoggerConfig coreCfg{};
    coreCfg.toStdout = true;
    coreCfg.toStderr = false;
    coreCfg.pattern  = "[CORE] %v";

    LoggerConfig clientCfg = coreCfg;
    clientCfg.pattern      = "[CLIENT] %v";

    constexpr int kThreads = 16;

    std::atomic<bool> start{false};

    // each thread will store its observed logger pointers here.
    std::vector<std::shared_ptr<spdlog::logger>> coreLoggers(kThreads);
    std::vector<std::shared_ptr<spdlog::logger>> clientLoggers(kThreads);

    std::vector<std::thread> threads;
    threads.reserve(kThreads);

    for (int i = 0; i < kThreads; ++i) {
        threads.emplace_back([i, &start, &coreLoggers, &clientLoggers, coreCfg, clientCfg]() {
            while (!start.load(std::memory_order_acquire)) {
                // spin
            }

            if (i == 0) {
                Logger::Init(coreCfg, clientCfg);
            } else if (i % 2 == 0) {
                Logger::Init();
            }

            auto &coreLogger   = Logger::GetCoreLogger();
            auto &clientLogger = Logger::GetClientLogger();

            coreLogger->info("core thread {}", i);
            clientLogger->info("client thread {}", i);

            coreLoggers[i]   = coreLogger;
            clientLoggers[i] = clientLogger;
        });
    }

    start.store(true, std::memory_order_release);

    for (auto &t : threads) {
        t.join();
    }

    EXPECT_TRUE(Logger::IsInitialized());

    ASSERT_NE(coreLoggers[0], nullptr);
    ASSERT_NE(clientLoggers[0], nullptr);

    for (int i = 0; i < kThreads; ++i) {
        EXPECT_EQ(coreLoggers[i], coreLoggers[0])   << "Core logger mismatch at thread " << i;
        EXPECT_EQ(clientLoggers[i], clientLoggers[0]) << "Client logger mismatch at thread " << i;
        EXPECT_NE(coreLoggers[i], nullptr)            << "Null core logger at thread " << i;
        EXPECT_NE(clientLoggers[i], nullptr)          << "Null client logger at thread " << i;
    }
}