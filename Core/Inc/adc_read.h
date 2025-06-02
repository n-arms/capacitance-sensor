#ifndef ADC_READ_H
#define ADC_READ_H

void adc_read_task(void *arguments);

struct adc_task_arguments {
	uint16_t low_voltage;
	uint16_t high_voltage;
};

#endif
