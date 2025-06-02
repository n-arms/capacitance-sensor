#include "adc_it.h"
#include "stm32f4xx_hal.h"
#include "tick.hpp"

struct adc_state {
	adc_config config;
	bool is_charging;
	tick charge_start;
};

union adc_state_ {
	adc_state state;
	struct {} unset;

	adc_state_() {
		unset = (typeof(unset)) {};
	}
} adc_state_global;
bool adc_state_global_set = false;

uint32_t elapsed_micros = 0;

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    if (adc_state_global_set && hadc->Instance == adc_state_global.state.config.hadc->Instance) {
        uint16_t adc_reading = HAL_ADC_GetValue(hadc);
        adc_state state = adc_state_global.state;

        bool charged = state.is_charging && adc_reading >= state.config.high_voltage;
        bool discharged = !state.is_charging && adc_reading <= state.config.low_voltage;

        if (charged || discharged) {
            tick now = tick::now();
            elapsed_micros = now.elapsed_since(state.charge_start);
            HAL_ADC_Stop_IT(hadc);
            osSemaphoreRelease(state.config.semaphore);
        }
    }
}

void init_adc_it(adc_config config) {
	adc_state_global.state = (adc_state) {
		config,
		true,
		tick::now()
	};
	adc_state_global_set = true;
}

void start_adc(bool is_charging) {
	if (!adc_state_global_set) return;
	adc_state &state = adc_state_global.state;

	state.is_charging = is_charging;
	state.charge_start = tick::now();
}

void start_adc_charging() {
	start_adc(true);
}

void start_adc_discharging() {
	start_adc(false);
}

uint32_t read_adc_elapsed() {
	return elapsed_micros;
}
