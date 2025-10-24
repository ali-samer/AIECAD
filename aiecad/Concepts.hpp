#pragma once

namespace aiecad {

template < typename T >
concept is_complete_type = requires { sizeof(T); };

} // namespace aiecad