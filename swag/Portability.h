#pragma once

#include <swag/swag-config.h>

#ifdef SWAG_HAVE_WEAK_SYMBOLS
#	if defined(__APPLE__) && defined(__MACH__)
#		define SWAG_ATTR_WEAK __attribute__((weak_import))
#	else
#		define SWAG_ATTR_WEAK __attribute__((weak))
#	endif
#else
#	define SWAG_ATTR_WEAK
#endif // SWAG_HAVE_WEAK_SYMBOLS