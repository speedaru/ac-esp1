#include <hook_fn.h>

uintptr_t FindExport(LPCSTR modName, LPCSTR exportName) {
	HMODULE hMod = GetModuleHandleA(modName);

	if (!hMod) {
		return 0;
	}
	else {
		return reinterpret_cast<uintptr_t>(GetProcAddress(hMod, exportName));
	}
}

char* __cdecl detourtEcho(char* String) {
	return hkEcho.CallTrampoline(String);
}

bool __cdecl detourHudEcho(char* String) {
	return hkHudEcho.CallTrampoline(String);
}

int __cdecl detourSay(char* Str) {
	return hkSay.CallTrampoline(Str);
}

bool __stdcall detourWglSwapBuffers(HDC hdc) {
	static NoRecoil hackNoRecoil;
	static ESP my_esp;

	// if mid unhook then dont call code
	if (hkwglSwapBuffers.IsUnhooking()) {
		hackNoRecoil.Off();
		my_esp.Off();
		return hkwglSwapBuffers.CallTrampoline(hdc); // Skip detour if unhooking
	}

	if (GetAsyncKeyState(VK_F1) & 1) { // no recoil
		hackNoRecoil.Toggle();
		my_esp.Toggle();
		if (hackNoRecoil.IsOn()) {
			EchoWithColor(ECHOCOLOR_GRAY, "[+] Toggled cheats on");
		}
		else {
			EchoWithColor(ECHOCOLOR_GRAY, "[-] Toggled cheats off");
		}
	}
	
	static uintptr_t ac_client = reinterpret_cast<uintptr_t>(GetModuleHandleA(NULL));
	Entity* localPlayer = *reinterpret_cast<Entity**>(ac_client + offsets::ac_client::localPlayer);
	Entity** entityList = *reinterpret_cast<Entity***>(ac_client + offsets::ac_client::entityList);
	int* gamemodePlayerCount = reinterpret_cast<int*>(ac_client + offsets::ac_client::gamemodePlayerCount);

	HDC currentHdc = wglGetCurrentDC();
	static HGLRC lastContext;
	HGLRC currentContext = wglGetCurrentContext();

	// Check for context change or initial load
	if (currentHdc != gl_draw::hdc || currentContext != lastContext || !gl_draw::fontInitialized) {
		gl_draw::InitFont();
		lastContext = currentContext;
	}

	// ---------- start drawing in 2d
	gl_draw::Begin2D();

	if (my_esp.IsOn()) {
		my_esp.Draw();
	}

	gl_draw::End2D();
	// ---------- stop drawing in 2d and restore 3d state

	return hkwglSwapBuffers.CallTrampoline(hdc);
}