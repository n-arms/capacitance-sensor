#include "adc_it.h"
#include "stm32f4xx_hal.h"

enum adc_state {
	ADC_OFF,
	ADC_CHARGING,
	ADC_DISCHARGING
};

adc_state state;
uint16_t high_voltage;
uint16_t low_voltage;
osMessageQueueId_t data_queue;

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    if (hadc->Instance == ADC1 && ADC_OFF != state) {
        uint16_t latest_adc_value = HAL_ADC_GetValue(hadc);

        //osMessageQueuePut(adc_data_queue, )
    }
}

void init_adc_it(adc_arguments arguments) {
	state = ADC_OFF;
	high_voltage = arguments.high_voltage;
	low_voltage = arguments.low_voltage;
	data_queue = arguments.data_queue;
}

void start_adc_it(ADC_HandleTypeDef *hadc) {
	state = ADC_CHARGING;
	HAL_ADC_Start_IT(hadc);
}
