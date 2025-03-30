#pragma once
#include <cstddef>

namespace offsets {
	namespace ac_client {
		const uintptr_t base = 0x0400000;
		const std::ptrdiff_t decAmmo = 0x637E9; // dec [esi]
		const std::ptrdiff_t localPlayer = 0x10F4F4;
		const std::ptrdiff_t entityList = 0x10F4F8;

		const std::ptrdiff_t fov = 0x10F1C4;

		const std::ptrdiff_t gamemodePlayerCount = 0x10F500;
		const std::ptrdiff_t gamemode = 0x10F49C;
		const std::ptrdiff_t matrix1 = 0x101AA8;
		const std::ptrdiff_t matrix2 = 0x101AE8;
		const std::ptrdiff_t matrix3 = 0x101B28;
		const std::ptrdiff_t matrix4 = 0x101B68;
	}

	namespace functions {
		const uintptr_t echo = 0x420250;
		const uintptr_t hudEcho = 0x420290;
		const uintptr_t say = 0x420210;
	}

	namespace static_addr {
		const uintptr_t callRecoilStart = 0x00463781; // push ebp
		const size_t callRecoilSize = 15; // push ebp
	}
}