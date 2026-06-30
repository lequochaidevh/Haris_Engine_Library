#pragma once

#include "Common/std17pch.hpp"
#include "Common/DebugMacroBuilt.h"

#include "Common/Logger/Logger.h"
#include "Common/Assert/Assert.h"

#include "Alias.h"

#define BIT(x) (1 << x)

#define HARIS_BIND_EVENT_FN(fn)                           \
    [this](auto&&... args) -> decltype(auto) {            \
        return fn(std::forward<decltype(args)>(args)...); \
    }
