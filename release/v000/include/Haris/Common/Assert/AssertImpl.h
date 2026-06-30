#pragma once
#include "Common/std17pch.hpp"

namespace Haris {

using AssertHandler = void (*)(const char* expr, const char* file, int line);

void default_assert_handler(const char* expr, const char* file, int line);

extern AssertHandler g_assert_handler;

inline void set_assert_handler(AssertHandler h) { g_assert_handler = h; }

}  // namespace Haris

#define RETURN_IF_ERROR(expr) \
    do {                      \
        auto _s = (expr);     \
        if (!_s.ok()) {       \
            return _s;        \
        }                     \
    } while (0)

#ifdef HARIS_ENABLE_ASSERTS
#define CORE_ASSERT(expr, ...)                              \
    do {                                                    \
        Haris::g_assert_handler(#expr, __FILE__, __LINE__); \
    } while (0)
#else
#define CORE_ASSERT(expr, ...)

#endif