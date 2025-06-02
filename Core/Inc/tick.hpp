#ifndef TICK_HPP
#define TICK_HPP

#include "cmsis_os.h"

class tick {
public:
	static tick now() {
		return tick(osKernelGetTickCount());
	}
	uint32_t elapsed_since(tick start) {
		return (millis - start.millis) * 1000;
	}
private:
	tick(uint32_t millis): millis(millis) {}
	uint32_t millis;

};

#endif
