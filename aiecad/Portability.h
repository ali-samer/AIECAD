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