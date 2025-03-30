#pragma once
#include <iostream>

class Hack {
protected:
	bool hackOn = false;

public:
	Hack() { }

	virtual void On() { }
	virtual void Off() { }
	void Toggle();

	inline bool IsOn() {
		return hackOn;
	}
};