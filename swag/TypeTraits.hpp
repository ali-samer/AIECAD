#pragma once

#include <cstddef>
#include <type_traits>

namespace swag {

template < class... >
inline constexpr bool always_false = false;

template < class Void , template < class... > class Op, class... Args>
struct is_detected : std::false_type {static_assert(!always_false<Void>,"");};

template < template < class... > class Op, class... Args >
struct is_detected<std::void_t<Op<Args...>>, Op, Args...> : std::true_type {};

template < template < class... > class Op, class... Args >
inline constexpr bool is_detected_v = is_detected<void, Op, Args...>::value;

template < class Default, class Void, template < class... > class Op , class... Args >
struct detector_or {
	using type = Default;
};

template < class Default, template < class... > class Op , class... Args >
struct detector_or<Default, std::void_t<Op<Args...>>, Op, Args...> {
	using type = Op<Args...>;
};

template < class Default, template < class... > class Op, class... Args>
using detector_or_t = typename detector_or<Default, void, Op, Args...>::type;
} // namespace swag