#pragma once

#include <cstdlib>   // std::abort
#include <cstdio>    // std::fprintf, std::fflush

namespace aiecad::detail
{
[[noreturn]] inline void HandleAssertFailure(
	const char* expr,
	const char* file,
	int         line,
	const char* function) noexcept
{
	std::fprintf(stderr,
		"========================================\n"
		" AIECAD ASSERTION FAILED\n"
		"----------------------------------------\n"
		"  Expression : %s\n"
		"  Location   : %s(%d)\n"
		"  Function   : %s\n"
		"========================================\n",
		expr, file, line, function);
	std::fflush(stderr);
	std::abort();
}
} // namespace aiecad::detail
