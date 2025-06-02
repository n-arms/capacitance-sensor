#ifndef ADC_IT_H
#define ADC_IT_H

#include "stm32f4xx_hal.h"
#include "cmsis_os.h"

struct adc_config {
	uint16_t high_voltage;
	uint16_t low_voltage;
	osSemaphoreId_t semaphore;
	ADC_HandleTypeDef *hadc;
};

// initialize the adc ISR
void init_adc_it(adc_config config);

// start measuring the voltage of a charging capacitor
void start_adc_charging();

// start measuring the voltage of a discharging capacitor
void start_adc_discharging();

// return the number of elapsed microseconds since the start of a capacitor measurement
uint32_t read_adc_elapsed();

#endif
