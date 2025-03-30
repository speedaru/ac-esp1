#include "echo.h"

void Echo(const char* format, ...) {
    // Buffer for the final string (max 256 chars, adjust if needed)
    char buffer[256];
    if (!buffer) return; // Memory allocation failed

    // Append formatted text
    va_list args;
    va_start(args, format);
    vsnprintf_s(buffer, sizeof(buffer), format, args); // Offset by 2 for \fX
    va_end(args);

    // Call original echo
    hkEcho.Call(buffer);
}
void EchoWithColor(ECHOCOLOR color, const char* format, ...) {
    // Buffer for the final string (max 256 chars, adjust if needed)
    char buffer[256];
    if (!buffer) return; // Memory allocation failed

    // Add color prefix (e.g., "\f1" for red)
    sprintf_s(buffer, sizeof(buffer), "\f%d", static_cast<int>(color));

    // Append formatted text
    va_list args;
    va_start(args, format);
    vsnprintf_s(buffer + 2, sizeof(buffer), sizeof(buffer) - 2, format, args); // Offset by 2 for \fX
    va_end(args);

    // Call original echo
    hkEcho.Call(buffer);
}

void HudEcho(const char* format, ...) {
    // Buffer for the final string (max 256 chars, adjust if needed)
    char buffer[256];
    if (!buffer) return; // Memory allocation failed

    // Append formatted text
    va_list args;
    va_start(args, format);
    vsnprintf_s(buffer, sizeof(buffer), format, args); // Offset by 2 for \fX
    va_end(args);

    // Call original echo
    hkHudEcho.Call(buffer);
}
void HudEchoWithColor(ECHOCOLOR color, const char* format, ...) {
    // Buffer for the final string (max 256 chars, adjust if needed)
    char buffer[256];
    if (!buffer) return; // Memory allocation failed

    // Add color prefix (e.g., "\f1" for red)
    sprintf_s(buffer, sizeof(buffer), "\f%d", static_cast<int>(color));

    // Append formatted text
    va_list args;
    va_start(args, format);
    vsnprintf_s(buffer + 2, sizeof(buffer), sizeof(buffer) - 2, format, args); // Offset by 2 for \fX
    va_end(args);

    // Call original echo
    hkHudEcho.Call(buffer);
}