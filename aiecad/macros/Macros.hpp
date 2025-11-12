#pragma once

#include <aiecad/macros/internal/Container.hpp>

#ifndef AIECAD_STRINGIZE
#	define AIECAD_STRINGIZE_IMPL(x) #x
#	define AIECAD_STRINGIZE(x) AIECAD_STRINGIZE_IMPL(x)
#endif // AIECAD_STRINGIZE
