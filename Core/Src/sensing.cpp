#include "sensing.h"
#include "stm32f4xx_hal.h"
#include "adc_it.h"
#include "kalman.hpp"
#include "math.h"

float measurement_variance = 1.;
float resistance_megaohm = 1.;

float estimate_capacitance(uint16_t delta_voltage, uint16_t elapsed_micros) {
	float k = -1. / (log(1 - delta_voltage / 3.3) * resistance_megaohm);
	return ((float) elapsed_micros) * k;
}

void sensing_task(void *arguments) {
	sensing_arguments *args = (sensing_arguments *) arguments;

	bool charging = true;
	kalman_filter cap_filter(0., 1.);

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

		uint16_t elapsed_micros = read_adc_elapsed();
		float cap_estimate = estimate_capacitance(args->delta_voltage, elapsed_micros);
		cap_filter.update(cap_estimate, measurement_variance);

		charging = !charging;
	}

	// error state
	for(;;) {

	}
}
