#include <hack.h>


void Hack::Toggle() {
	if (hackOn) {
		Off();
	}
	else if (!hackOn) {
		On();

	}
}