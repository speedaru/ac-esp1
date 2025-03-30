#pragma once
#include <iostream>
#include <stdarg.h>

#include "hook_fn.h"

enum ECHOCOLOR {
    ECHOCOLOR_GREEN = 0,
    ECHOCOLOR_BLUE = 1,
    ECHOCOLOR_YELLOW = 2,
    ECHOCOLOR_RED = 3,
    ECHOCOLOR_GRAY = 4,
    ECHOCOLOR_WHITE = 5,
    ECHOCOLOR_DARK_BROWN = 6,
    ECHOCOLOR_DARK_RED = 7,
    ECHOCOLOR_PURPLE = 8,
    ECHOCOLOR_ORANGE = 9,
};

void Echo(const char* format, ...);
void EchoWithColor(ECHOCOLOR color, const char* format, ...);

void HudEcho(const char* format, ...);
void HudEchoWithColor(ECHOCOLOR color, const char* format, ...);