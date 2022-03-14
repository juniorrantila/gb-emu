#pragma once
#ifdef NDEBUG
inline constexpr const bool is_debug_build = false;
#else
inline constexpr const bool is_debug_build = true;
#endif
