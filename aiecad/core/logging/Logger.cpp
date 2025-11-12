//
// Created by Samer Ali on 10/31/25.
//

#include <aiecad/core/logging/Logger.hpp>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/null_sink.h>

#include <iostream>

namespace aiecad {

namespace {
// this builds a list of sinks according to LoggerConfig.
std::vector<spdlog::sink_ptr> make_sinks(const LoggerConfig &config) {
	std::vector<spdlog::sink_ptr> sinks;

	if (config.toStdout) {
		auto sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		sink->set_pattern(config.pattern);
		sinks.push_back(sink);
	}

	if (config.toStderr) {
		auto sink = std::make_shared<spdlog::sinks::stderr_color_sink_mt>();
		sink->set_pattern(config.pattern);
		sinks.push_back(sink);
	}

	if (not config.toFile.empty()) {
		auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(
			config.toFile.string(), /*truncate=*/true);
		sink->set_pattern(config.pattern);
		sinks.push_back(sink);
	}

	if (sinks.empty()) {
		auto sink = std::make_shared<spdlog::sinks::null_sink_mt>();
		sink->set_pattern(config.pattern);
		sinks.push_back(sink);
	}

	return sinks;
}
} // namespace

void Logger::Init(const LoggerConfig &coreConfig,
                  const LoggerConfig &clientConfig) noexcept {
	if (IsInitialized()) {
		AIECAD_CORE_WARN("Logger already configured and initialized");
		return;
	}

	std::call_once(m_initFlag, [&]() {
		m_coreConfig   = coreConfig;
		m_clientConfig = clientConfig;
		InitImpl();
	});
}

void Logger::Init() noexcept {
	std::call_once(m_initFlag, []() {
		InitImpl();
	});
}

void Logger::InitImpl() noexcept {
	try {
		auto coreSinks   = make_sinks(m_coreConfig);
		auto clientSinks = make_sinks(m_clientConfig);

		m_coreLogger = std::make_shared<spdlog::logger>(
			"AIECAD CORE", coreSinks.begin(), coreSinks.end());
		m_coreLogger->set_level(
			static_cast<spdlog::level::level_enum>(m_coreConfig.level));

		m_coreLogger->flush_on(spdlog::level::warn);

		spdlog::set_default_logger(m_coreLogger);

		m_clientLogger = std::make_shared<spdlog::logger>(
			"AIECAD APP", clientSinks.begin(), clientSinks.end());
		m_clientLogger->set_level(
			static_cast<spdlog::level::level_enum>(m_clientConfig.level));

		m_clientLogger->flush_on(spdlog::level::warn);
		m_initialized = true;
		return;
	} catch (const spdlog::spdlog_ex &e) {
#ifdef AIECAD_DEBUG
		std::cerr << "Logger init failed (spdlog_ex): " << e.what() << '\n';
#endif
	} catch (const std::exception &e) {
#ifdef AIECAD_DEBUG
		std::cerr << "Logger init failed (std::exception): " << e.what() << '\n';
#endif
	} catch (...) {
#ifdef AIECAD_DEBUG
		std::cerr << "Logger init failed (exception unknown)...\n";
#endif
	}

	m_initialized = false;
}

bool Logger::IsInitialized() noexcept { return m_initialized; }

std::shared_ptr<spdlog::logger> &Logger::GetCoreLogger() {
	Init();
	return m_coreLogger;
}

std::shared_ptr<spdlog::logger> &Logger::GetClientLogger() {
	Init();
	return m_clientLogger;
}

LoggerConfig Logger::GetCoreConfig() noexcept {
	Init(); // make sure we initialized.

	// m_coreConfig is a static shared object. It's safe to copy here because:
	//  - Initialization is protected by std::call_once (only one thread writes)
	//  - After initialization, the config is treated as immutable (read-only)
	//  - Concurrent reads and copies from an immutable object are thread-safe
	return m_coreConfig;
}

LoggerConfig Logger::GetClientConfig() noexcept {
	Init(); // make sure we initialized.

	// m_clientConfig is a static shared object. It's safe to copy here because:
	//  - Initialization is protected by std::call_once (only one thread writes)
	//  - After initialization, the config is treated as immutable (read-only)
	//  - Concurrent reads and copies from an immutable object are thread-safe
	return m_clientConfig;
}
} // aiecad