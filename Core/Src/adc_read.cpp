#include "main.h"
#include "cmsis_os.h"
#include "adc_read.h"

uint16_t read_adc() {
    return 42;
}

void adc_read_task(void *arguments) {
	adc_task_arguments *args = (adc_task_arguments *)arguments;

    for (;;) {
    	// uncharged capacitor
    	uint32_t start_tick = osKernelGetTickCount();
    	while (read_adc() < args->high_voltage);
    	uint32_t end_tick = osKernelGetTickCount();
    	while (read_adc() > args->low_voltage);
    }
}
