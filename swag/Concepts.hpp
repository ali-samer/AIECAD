#pragma once

namespace swag {

template < typename T >
concept is_complete_type = requires { sizeof(T); };

} // namespace swag