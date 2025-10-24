#pragma once

#define SWAG_DECLVAL(...) static_cast<__VA_ARGS__ (*)() noexcept>(nullptr)()