#include "norecoil.h"


void NoRecoil::On() {
	if (hackOn) {
		return;
	}

	// get original bytes
	if (std::all_of(originalBytes.begin(), originalBytes.end(), [] (uint8_t b) { return b == 0; })) {
		mem::ReadBytes(callRecoilStart, originalBytes.data(), sizeToPatch);
	}

	mem::NopEx((BYTE*)callRecoilStart, sizeToPatch);
	hackOn = true;
}

void NoRecoil::Off() {
	if (!hackOn) {
		return;
	}

	// if original bytes 0
	if (std::all_of(originalBytes.begin(), originalBytes.end(), [](uint8_t b) { return b == 0; })) {
		return;
	}

	mem::PatchEx((BYTE*)callRecoilStart, originalBytes.data(), sizeToPatch);
	hackOn = false;
}