#pragma once
#include <cstdint>

namespace aiecad {

// Adds a+b but clamps the result to [lo, hi].
int clamp_add(int a, int b, int lo, int hi);

} // namespace swakit
