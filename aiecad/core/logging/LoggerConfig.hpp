#pragma once

#include <spdlog/spdlog.h>

#include <filesystem>
#include <string>
#include <cstddef>

namespace aiecad {
/**
 * @enum LoggerLevel
 * @brief Defines the severity levels for log messages.
 *
 * This enumeration represents different verbosity or importance levels
 * that can be assigned to log entries. They can be used to control which
 * messages get emitted or filtered out depending on the configured log level.
 *
 * Typical usage:
 * - `Trace` and `Debug` are for detailed internal information useful
 *    during development or troubleshooting.
 * - `Info` is for high-level messages that show normal application flow.
 * - `Warn` indicates something unexpected but non-fatal.
 * - `Error` indicates a recoverable failure or significant issue.
 * - `Critical` indicates a severe, unrecoverable error requiring immediate attention.
 * - `Off` disables logging entirely.
 */
enum class LoggerLevel {
	/// Extremely detailed diagnostic information, usually disabled in production.
	Trace = static_cast<int>(spdlog::level::trace),

	/// Fine-grained informational events useful for debugging.
	Debug = static_cast<int>(spdlog::level::debug),

	/// General informational messages that highlight application progress.
	Info = static_cast<int>(spdlog::level::info),

	/// Potentially harmful situations or unexpected states.
	Warn = static_cast<int>(spdlog::level::warn),

	/// Error events that might still allow the application to continue running.
	Error = static_cast<int>(spdlog::level::err),

	/// Severe error events that will presumably lead the application to abort.
	Critical = static_cast<int>(spdlog::level::critical),

	/// Turns off all logging output.
	Off = static_cast<int>(spdlog::level::off),
};


/**
 * @struct LoggerConfig
 * @brief Configuration settings for the application's logging system.
 *
 * This structure defines all configurable parameters for initializing
 * and controlling the behavior of the logger. It allows fine-tuning
 * of output destinations, formatting, and logging verbosity.
 *
 * Example usage:
 * @code
 * LoggerConfig config;
 * config.level = LoggerLevel::Debug;
 * config.toFile = "aiecad.log";
 * config.toStdout = true;
 * config.pattern = "[%T] [%^%l%$] %v";
 * Logger::init(config);
 * @endcode
 */
struct LoggerConfig {
	/**
	 * @brief Minimum log level to record or display.
	 *
	 * Messages below this level are ignored. For example, if `level` is set to
	 * `LoggerLevel::Warn`, only `Warn`, `Error`, and `Critical` messages will be logged.
	 * Defaults to `LoggerLevel::Info`.
	 */
	LoggerLevel level = LoggerLevel::Info;

	/**
	 * @brief Optional file path for log output.
	 *
	 * If specified, log messages will also be written to this file.
	 * If left empty, no log file is created.
	 */
	std::filesystem::path toFile{ };

	/**
	 * @brief Whether to print log messages to standard output (stdout).
	 *
	 * Defaults to `true`. Useful for launching and debugging AIECAD on CLI.
	 */
	bool toStdout = true;

	/**
	 * @brief Whether to print log messages to standard error (stderr).
	 *
	 * Defaults to `false`. Can be enabled for critical-only or diagnostic logging.
	 */
	bool toStderr = false;

	/**
	 * @brief Format pattern for log messages.
	 *
	 * This pattern controls the structure and appearance of log messages.
	 * Common placeholders:
	 * - `%T`: Timestamp
	 * - `%l`: Log level
	 * - `%n`: Logger name
	 * - `%v`: The log message
	 * - `%^` / `%$`: Begin/end color formatting
	 *
	 * Default: `[%T] [%^%l%$] %n: %v`
	 */
	std::string pattern = "[%T] [%^%l%$] %n: %v";

	// TODO: experiment with following capabilities before refactoring logger API
	// bool async = false;
	// std::size_t asyncQueueSize = 8192;
};
} // namespace aiecad
