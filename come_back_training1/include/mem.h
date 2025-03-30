#pragma once
#include <Windows.h>
#include <vector>

namespace mem
{
	void PatchEx(BYTE* dst, BYTE* src, unsigned int size);
	void NopEx(BYTE* dst, unsigned int size);

	uintptr_t FindDMMAAddy(uintptr_t baseAddress, int baseOffset, std::vector<int> offsets);

	bool Detour(BYTE* src, BYTE* dst, uintptr_t len);
	inline bool Detour(void* src, void* dst, uintptr_t len) {
		return Detour((BYTE*)src, (BYTE*)dst, len);
	}

	BYTE* TrampolineHook(BYTE* src, BYTE* dst, uintptr_t len);
	inline BYTE* TrampolineHook(void* src, void* dst, uintptr_t len) {
		return TrampolineHook((BYTE*)src, (BYTE*)dst, len);
	}

	void ReadBytes(uintptr_t addr, void* buffer, size_t size);
};