#include <main.h>

DWORD HackThread(HMODULE hmod) {
	// init minhook
	if (MH_Initialize() != MH_OK) {
		fprintf(stderr, "failed to init minhook\n");
		return 1;
	}

	hkEcho = Hook<tEcho>(offsets::functions::echo, detourtEcho);
	hkHudEcho = Hook<tHudEcho>(offsets::functions::hudEcho, detourHudEcho);
	hkHudEcho.Enable();

	HudEchoWithColor(ECHOCOLOR_YELLOW, "Loaded cheats");

	hkwglSwapBuffers = Hook<twglSwapBuffers>(FindExport("opengl32.dll", "wglSwapBuffers"), reinterpret_cast<void*>(detourWglSwapBuffers));
	hkwglSwapBuffers.Enable();

	while (hkwglSwapBuffers.GetEnabled()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
		if (GetAsyncKeyState(VK_END) & 1) {
			hkwglSwapBuffers.Unhook();
		}
	}
	gl_draw::CleanupFont();

	HudEchoWithColor(ECHOCOLOR_ORANGE, "Unloaded cheats");

	// unhook hooks
	hkHudEcho.Unhook();
	hkEcho.Unhook();

	MH_Uninitialize();
	FreeLibraryAndExitThread(hmod, 0);
	return 0;
}

BOOL WINAPI DllMain(HMODULE hmod, DWORD dwreason, LPVOID reserved) {
	static FILE* f;

	switch (dwreason) {
	case DLL_PROCESS_ATTACH:
		AllocConsole();
		freopen_s(&f, "CONOUT$", "w", stdout);

		CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)HackThread, hmod, NULL, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		fclose(f);
		FreeConsole();
		break;
	}

	return TRUE;
}