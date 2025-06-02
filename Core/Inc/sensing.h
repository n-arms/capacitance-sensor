#ifndef SENSING_H
#define SENSING_H

#include "cmsis_os.h"
#include "stm32f4xx_hal.h"

void sensing_task(void *arguments);

struct sensing_arguments {
	osSemaphoreId_t adc_it_semaphore;
	GPIO_TypeDef *step_gpio;
	uint16_t step_number;
	uint16_t delta_voltage;
};

#endif
