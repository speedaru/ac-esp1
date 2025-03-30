#include <mem.h>

void mem::PatchEx(BYTE* dst, BYTE* src, unsigned int size)
{
	DWORD oldProtect;

	// save previous settings
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldProtect);

	// write new data byte by byte
	for (unsigned int i = 0; i < size; i++)
		*(BYTE*)(dst + i) = *(BYTE*)(src + i);

	// set back old permissions
	VirtualProtect(dst, size, oldProtect, &oldProtect);
}
void mem::NopEx(BYTE* dst, unsigned int size)
{
	BYTE* nopArray = new BYTE[size];
	memset(nopArray, 0x90, size);

	PatchEx(dst, nopArray, size);
	delete[] nopArray;
}

uintptr_t mem::FindDMMAAddy(uintptr_t baseAddress, int baseOffset, std::vector<int> offsets)
{
	uintptr_t finalAddress = baseAddress + baseOffset;

	for (int offset : offsets)
	{
		finalAddress = *(uintptr_t*)finalAddress;
		finalAddress += offset;
	}

	return finalAddress;
}

bool mem::Detour(BYTE* src, BYTE* dst, uintptr_t len) {
	if (len < 5) {
		return false;
	}

	// change protection so we can write
	DWORD originalProtect;
	VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &originalProtect);

	// calculate relative address to jump to dst
	uintptr_t relativeJumpAddr = dst - src - 5;

	// write jump and addr
	*src = 0xE9; // steal bytes and add jmp
	*(uintptr_t*)(src + 1) = relativeJumpAddr; // add addr to jump to after jmp
	printf("Detour: relative addr of hooked fn: %X\n", relativeJumpAddr);

	// reset protection
	VirtualProtect(src, len, originalProtect, &originalProtect);

	return true;
}
BYTE* mem::TrampolineHook(BYTE* src, BYTE* dst, uintptr_t len) {
	if (len < 5) {
		return 0;
	}

	// create gateway
	BYTE* gateway = reinterpret_cast<BYTE*>(VirtualAlloc(0, len, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE));

	// write stolen bytes to gateway
	memcpy_s(gateway, len, src, len);

	// calculate relative address to jump to gateway
	uintptr_t originalCodeRelativeAddr = src - gateway - 5;
	printf("TrampolineHook: relative addr of og fn: %X\n", originalCodeRelativeAddr);

	// write jump and relative addr to end of gateway
	*(BYTE*)(gateway + len) = 0xE9;
	*(uintptr_t*)(gateway + len + 1) = originalCodeRelativeAddr;

	Detour(src, dst, len);

	return gateway;
}

void mem::ReadBytes(uintptr_t addr, void* buffer, size_t size) {
	memcpy_s(buffer, size, reinterpret_cast<void*>(addr), size);
}