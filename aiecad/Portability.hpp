#pragma once

#include <aiecad/aiecad-config.h>

#ifdef AIECAD_HAVE_WEAK_SYMBOLS
#	if defined(__APPLE__) && defined(__MACH__)
#		define AIECAD_ATTR_WEAK __attribute__((weak_import))
#	else
#		define AIECAD_ATTR_WEAK __attribute__((weak))
#	endif
#else
#	define AIECAD_ATTR_WEAK
#endif // AIECAD_HAVE_WEAK_SYMBOLS

#if defined(_WIN32) || defined(_WIN64)
#	define AIECAD_PLATFORM_WINDOWS 1
#else
#	define AIECAD_PLATFORM_WINDOWS 0
#endif

#if defined(__APPLE__)
#	define AIECAD_PLATFORM_MACOSX 1
#else
#	define AIECAD_PLATFORM_MACOSX 0
#endif

#if defined(__linux__)
#	define AIECAD_PLATFORM_LINUX 1
#else
#	define AIECAD_PLATFORM_LINUX 0
#endif