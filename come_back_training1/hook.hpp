#pragma once
#include <Windows.h>
#include <type_traits>
#include <utility>

#include <minhook/MinHook.h>


template <typename T>
class Hook {
private:
    T target;           // Address of fn to hook (e.g., 0x00420290)
    T trampoline;       // Copy of original function after hooking
    bool enabled;       // Hook status
    void* detour;       // Detour function pointer

    CRITICAL_SECTION cs; // For thread safety
    volatile bool unhooking = false; // Signals the detour to skip

public:
    // Constructor: takes target address and detour function
    Hook() {}
    Hook(uintptr_t targetAddr, void* detourFunc)
        : target(reinterpret_cast<T>(targetAddr)), trampoline(nullptr), enabled(false), detour(detourFunc) {
        InitializeCriticalSection(&cs);
        // Initialize MinHook globally once (e.g., in DllMain)
        if (MH_CreateHook(reinterpret_cast<LPVOID>(target), detour, reinterpret_cast<LPVOID*>(&trampoline)) == MH_OK) {
            //printf("Hooked function at 0x%X\n", (uintptr_t)target);
        }
        else {
            printf("Failed to create hook at 0x%X\n", (uintptr_t)target);
        }
    }
    // Destructor: cleanup hook
    ~Hook() {
        Unhook();
        DeleteCriticalSection(&cs);
    }


    void Enable() {
        EnterCriticalSection(&cs);
        if (!enabled) {
            MH_STATUS status;
            if ((status = MH_EnableHook(reinterpret_cast<LPVOID>(target))) == MH_OK) {
                enabled = true;
            }
            else {
                printf("failed to enable hook\n");
                printf("mhstats: %d\n", status);
            }
        }
        LeaveCriticalSection(&cs);
    }
    void Disable() {
        EnterCriticalSection(&cs);
        if (enabled) {
            if (MH_DisableHook(reinterpret_cast<LPVOID>(target)) == MH_OK) {
                enabled = false;
            }
            else {
                printf("failed to disable hook\n");
            }
        }
        LeaveCriticalSection(&cs);
    }
    void Toggle() {
        if (enabled) {
            Disable();
        }
        else if (!enabled) {
            Enable();
        }
    }
    void Unhook() {
        EnterCriticalSection(&cs); // Protect this block
        if (enabled) {
            unhooking = true; // Tell detour to stop running
            Sleep(50); // Wait 50ms for any active detour to finish
            MH_DisableHook(target); // Disable the hook
            Sleep(50); // Wait 50ms for any active detour to finish
            MH_RemoveHook(target); // Remove the hook
            enabled = false; // Mark as unhooked
            unhooking = false; // Reset the flag
        }
        LeaveCriticalSection(&cs); // Release the lock
    }

    template <typename... Args>
    auto Call(Args&&... args) -> std::invoke_result_t<T, Args...> {
        if (target == nullptr) {
            printf("Error: Target not initialized\n");
            throw "Target not available";
        }
        return target(std::forward<Args>(args)...);
    }

    template <typename... Args>
    auto CallTrampoline(Args&&... args) -> std::invoke_result_t<T, Args...> {
        if (trampoline == nullptr) {
            printf("Error: Trampoline not initialized for 0x%X\n", (uintptr_t)target);
            throw "Trampoline not available";
        }
        return trampoline(std::forward<Args>(args)...);
    }

    

    // Check hook status
    bool HookEnabled() const { return enabled; }

    T GetTrampoline() const {
        return trampoline;
    }
    T GetTarget() const {
        return target;
    }

    inline bool GetEnabled() {
        return enabled;
    }
    inline bool IsUnhooking() {
        return unhooking;
    }
};