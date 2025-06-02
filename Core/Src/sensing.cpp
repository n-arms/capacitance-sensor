#include "sensing.h"
#include "stm32f4xx_hal.h"
#include "adc_it.h"

void sensing_task(void *arguments) {
	sensing_arguments *args = (sensing_arguments *) arguments;

	bool charging = true;

	for(;;) {
		// pull vstep high or low
		if (charging) {
			HAL_GPIO_WritePin(args->step_gpio, args->step_number, GPIO_PIN_SET);
			start_adc_charging();
		} else {
			HAL_GPIO_WritePin(args->step_gpio, args->step_number, GPIO_PIN_RESET);
			start_adc_discharging();
		}

		if (osSemaphoreAcquire(args->adc_it_semaphore, 0) != osOK) break;

		uint32_t elapsed_millis = read_adc_elapsed();
	}

	// error state
	for(;;) {

	}
}
