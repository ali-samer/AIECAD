#pragma once

#include <aiecad/core/logging/LoggerConfig.hpp>
#include <aiecad/Portability.hpp>
#include <aiecad/macros/Macros.hpp>
#include <aiecad/utils/Assert.hpp>

#include <spdlog/spdlog.h>

#include <memory>		// for std::shared_ptr & std::make_shared
#include <mutex>		// for std::call_once & std::once_flag
#include <stdexcept>	// for std::runtime_error in AIECAD_ASSERT
#include <atomic>

namespace aiecad {
class Logger final {
public:
	static void Init(const LoggerConfig &coreConfig,
	                 const LoggerConfig &clientConfig = LoggerConfig()) noexcept;
	static void Init() noexcept;

	static bool IsInitialized() noexcept;

	static std::shared_ptr<spdlog::logger> &GetClientLogger();
	static std::shared_ptr<spdlog::logger> &GetCoreLogger();

	static LoggerConfig GetCoreConfig() noexcept;
	static LoggerConfig GetClientConfig() noexcept;
private:
	// This member function is not thread-safe! It must only be called within `Init` member functions
	// which wrap it in a `std::call_once`.
	// It serves as the implementation for two `Init` methods to avoid repeating logic.
	static void InitImpl() noexcept;

	static inline std::shared_ptr<spdlog::logger> m_clientLogger{ };
	static inline std::shared_ptr<spdlog::logger> m_coreLogger{ };
	static inline LoggerConfig m_coreConfig{ };
	static inline LoggerConfig m_clientConfig{ };
	static inline std::once_flag m_initFlag;
	static inline std::atomic<bool> m_initialized{ false };
};
} // namespace aiecad

#if AIECAD_ENABLE_LOGGING
#	define AIECAD_CORE_LOGGER         ::aiecad::Logger::GetCoreLogger()
#	define AIECAD_CLIENT_LOGGER       ::aiecad::Logger::GetClientLogger()

#	define AIECAD_CORE_TRACE(...)     AIECAD_CORE_LOGGER->trace(__VA_ARGS__)
#	define AIECAD_CORE_INFO(...)      AIECAD_CORE_LOGGER->info(__VA_ARGS__)
#	define AIECAD_CORE_WARN(...)      AIECAD_CORE_LOGGER->warn(__VA_ARGS__)
#	define AIECAD_CORE_ERROR(...)     AIECAD_CORE_LOGGER->error(__VA_ARGS__)
#	define AIECAD_CORE_FATAL(...)     AIECAD_CORE_LOGGER->critical(__VA_ARGS__)

#	define AIECAD_TRACE(...)          AIECAD_CLIENT_LOGGER->trace(__VA_ARGS__)
#	define AIECAD_INFO(...)           AIECAD_CLIENT_LOGGER->info(__VA_ARGS__)
#	define AIECAD_WARN(...)           AIECAD_CLIENT_LOGGER->warn(__VA_ARGS__)
#	define AIECAD_ERROR(...)          AIECAD_CLIENT_LOGGER->error(__VA_ARGS__)
#	define AIECAD_FATAL(...)          AIECAD_CLIENT_LOGGER->critical(__VA_ARGS__)

#	define AIECAD_CORE_GET_CONFIG()	::aiecad::Logger::GetCoreConfig()
#	define AIECAD_CLIENT_GET_CONFIG()	::aiecad::Logger::GetClientConfig()
#else
#	define AIECAD_CORE_LOGGER
#	define AIECAD_CLIENT_LOGGER

#	define AIECAD_CORE_TRACE(...)
#	define AIECAD_CORE_INFO(...)
#	define AIECAD_CORE_WARN(...)
#	define AIECAD_CORE_ERROR(...)
#	define AIECAD_CORE_FATAL(...)

#	define AIECAD_TRACE(...)
#	define AIECAD_INFO(...)
#	define AIECAD_WARN(...)
#	define AIECAD_ERROR(...)
#	define AIECAD_FATAL(...)

#	define AIECAD_CORE_GET_CONFIG() NULL
#	define AIECAD_CLIENT_GET_CONFIG() NULL
#endif

//  TODO: Nice to have functions. Need implementation
// #define AIECAD_CORE_DISABLE_LOGGER(...)     AIECAD_CORE_LOGGER::DisableLogging(__VA_ARGS__);
// #define AIECAD_CLIENT_DISABLE_LOGGER(...)   AIECAD_CLIENT_LOGGER::DisableLogging(__VA_ARGS__);
// #define AIECAD_CORE_ENABLE_LOGGER(...)      AIECAD_CORE_LOGGER::EnableLogging(__VA_ARGS__);
// #define AIECAD_CLIENT_ENABLE_LOGGER(...)    AIECAD_CLIENT_LOGGER::EnableLogging(__VA_ARGS__);

#if AIECAD_ENABLE_ASSERTS
#define AIECAD_ASSERT(cond, ...)														\
    do {																				\
        if (!(cond)) {																	\
            AIECAD_ERROR(																\
                "Assertion failed: {}\n  File: {}\n  Line: {}\n  Func: {}",				\
                #cond, __FILE__, __LINE__, __func__);									\
            AIECAD_ERROR("" __VA_ARGS__);												\
            ::aiecad::detail::HandleAssertFailure(#cond, __FILE__, __LINE__, __func__); \
        }																				\
    } while (0)

#else
#	define AIECAD_ASSERT(cond, ...)
#endif