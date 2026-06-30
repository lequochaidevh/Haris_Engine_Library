#pragma once

#include "Haris.h"

#if !defined(CHECKER_BOARD_PATH) && !defined(TEXTURE_SHADER_PATH) && \
    !defined(HARIS_LOGO_PATH) && !defined(BASIC_TEXTURE_SHADER_PATH)
#define CHECKER_BOARD_PATH        "/tmp"
#define HARIS_LOGO_PATH           "/tmp"
#define TEXTURE_SHADER_PATH       "/tmp"
#define BASIC_TEXTURE_SHADER_PATH "/tmp"
#endif