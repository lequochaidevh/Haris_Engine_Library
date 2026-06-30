#pragma once

#include <cstdio>

namespace DebugMacroBuilt {

inline void CheckAllConfigs() {
    printf("--- Build Configuration ---\n");

    printf("HARIS_ENABLE_ASSERTS: %s\n",
#ifdef HARIS_ENABLE_ASSERTS
           "ON"
#else
           "OFF"
#endif
    );

    printf("HARIS_ENABLE_LOGGER: %s\n",
#ifdef HARIS_ENABLE_LOGGER
           "ON"
#else
           "OFF"
#endif
    );

    printf("---------------------------\n");
}

constexpr void CheckMacroInEngine() {
    printf("--- Build Engine Configuration ---\n");

    printf("HARIS_ENABLE_ASSERTS: %s\n",
#ifdef HARIS_ENABLE_ASSERTS
           "ON"
#else
           "OFF"
#endif
    );

    printf("HARIS_ENABLE_LOGGER: %s\n",
#ifdef HARIS_ENABLE_LOGGER
           "ON"
#else
           "OFF"
#endif
    );

    printf("---------------------------\n");
}

}  // namespace DebugMacroBuilt