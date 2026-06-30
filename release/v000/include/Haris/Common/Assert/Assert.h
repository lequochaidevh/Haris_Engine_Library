#pragma once
#include "AssertImpl.h"

// Runtime assert
#ifdef HARIS_ENABLE_ASSERTS
#if defined(PLATFORM_LINUX)
#define H_DEBUGBREAK() raise(SIGTRAP)
#elif defined(PLATFORM_WINDOWS)
#define H_DEBUGBREAK() __debugbreak()
#else
#define H_DEBUGBREAK()
#endif

#define HARIS_ASSERT(x, msg, ...)      \
    if (!(x)) {                        \
        CORE_ASSERT(msg, __VA_ARGS__); \
        H_DEBUGBREAK();                \
    }
#define HARIS_CORE_ASSERT(x, msg, ...) \
    if (!(x)) {                        \
        CORE_ASSERT(msg, __VA_ARGS__); \
        H_DEBUGBREAK();                \
    }
#else
#define HARIS_ASSERT(x, ...)
#define HARIS_CORE_ASSERT(x, ...)
#endif

namespace Haris {}  // namespace Haris