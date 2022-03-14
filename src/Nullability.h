#pragma once

#ifdef __clang__
#define nullable _Nullable
#define nonnull  _Nonnull
#else
#define nullable
#define nonnull
#endif
