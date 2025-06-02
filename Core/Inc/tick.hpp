#ifndef TICK_HPP
#define TICK_HPP

#include "cmsis_os.h"

class tick {
public:
	static tick now() {
		return tick(osKernelGetTickCount());
	}
private:
	explicit tick(unint32_t millis): millis(millis) {}
	uint32_t millis;

};

#endif
