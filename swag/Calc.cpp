#include <cstdint>

#include <swag/Calc.hpp>

namespace swag{

// Adds a+b but clamps the result to [lo, hi].
int clamp_add(int a, int b, int lo, int hi) {
	long long s = static_cast<long long>(a) + static_cast<long long>(b);
	if (s < lo) return lo;
	if (s > hi) return hi;
	return static_cast<int>(s);
}

} // namespace swakit
