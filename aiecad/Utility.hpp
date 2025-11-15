#pragma once

// https://github.com/facebook/folly/blob/3f9ad9e19631c4ba4401060df7206e2147a825a0/folly/Utility.h#L31
#define SWAG_DECLVAL(...) static_cast<__VA_ARGS__ (*)() noexcept>(nullptr)()