#pragma once
#include <Windows.h>
#include <iostream>
#include <thread>
#include <iostream>

#include <minhook/MinHook.h>

#include "hack.h"
#include "norecoil.h"
#include "hook.hpp"
#include "gldraw.h"
//#include "gltext.h"
//#include "hackgl.h"
#include "offsets.h"
#include "assaultcube.h"
#include "esp.h"
#include "echo.h"

// wglSwapBuffers fn pointer typedef
typedef bool(__stdcall* twglSwapBuffers)(HDC hdc);
bool __stdcall detourWglSwapBuffers(HDC hdc);

inline Hook<twglSwapBuffers> hkwglSwapBuffers;

// echo
typedef char* (__cdecl* tEcho)(char* String);
char* __cdecl detourtEcho(char* String);

inline Hook<tEcho> hkEcho;

// hudecho
typedef char* (__cdecl* tHudEcho)(char* String);
bool __cdecl detourHudEcho(char* String);

inline Hook<tHudEcho> hkHudEcho;

// say
typedef int(__cdecl* tSay)(char* Str);
int __cdecl detourSay(char* Str);

inline Hook<tSay> hkSay;


uintptr_t FindExport(LPCSTR modName, LPCSTR exportName);

//class Entity
//{
//public:
//	char pad_0000[4]; //0x0000
//	float x; //0x0004
//	float y; //0x0008
//	float z; //0x000C
//	char pad_0010[232]; //0x0010
//	int32_t health; //0x00F8
//	int32_t armor; //0x00FC
//	char pad_0100[293]; //0x0100
//	char name[12]; //0x0225
//	char pad_0231[537]; //0x0231
//}; //Size: 0x044A