#pragma once
#include <algorithm>

#include "offsets.h"
#include "mem.h"
#include "hack.h"

class NoRecoil : public Hack {
private:
	const uintptr_t callRecoilStart = offsets::static_addr::callRecoilStart;
	const size_t sizeToPatch = offsets::static_addr::callRecoilSize;
	std::vector<uint8_t> originalBytes;

public:
	NoRecoil() {
		originalBytes = std::vector<uint8_t>(sizeToPatch);
	}

	~NoRecoil() {
		Off();
	}

	void On() override;
	void Off() override;
};