#ifndef ADC_IT_H
#define ADC_IT_H

#include "cmsis_os.h"

struct adc_arguments {
	uint16_t high_voltage;
	uint16_t low_voltage;
	osMessageQueueId_t data_queue;
};

void init_adc_it(adc_arguments arguments);
void start_adc_it();

#endif
