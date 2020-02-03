#ifndef _ADC_H
#define _ADC_H

#include "utils.h"
#include <display.h>
#include <led.h>
#include <stdlib.h>
#include <stm32f3xx_ll_adc.h>
#include <stm32f3xx_ll_gpio.h>
#include <stm32f3xx_ll_rcc.h>

#define ENABLE_TEMPERATURE_INPUT_GPIO LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA)
#define TEMPERATURE_PORT GPIOC
#define TEMPERATURE_PIN LL_GPIO_PIN_2
#define SUPPLY_VOLTAGE 3.0f
#define ADC_RESOLUTION 4095.0f
#define EXEMPLARY_RESISTOR 1942.0f
#define SUPPLY_VOLTAGE 3.0f
#define SAMPLES_NUMBER 1000

#define CALCULATE_ADC_VOLTAGE(ADC_VALUE) (SUPPLY_VOLTAGE * ADC_AVG_VALUE) / ADC_RESOLUTION
#define CALCULATE_ADC_PERCENTAGE(ADC_VALUE) (ADC_AVG_VALUE / ADC_RESOLUTION) * 100.0f
#define CALCULATE_TERMISTOR_RESISTANCE(ADC_VALUE)                                                  \
    (unsigned int)(EXEMPLARY_RESISTOR / (ADC_RESOLUTION / (float)ADC_AVG_VALUE - 1.0f))

#define INTERVAL_MIN_RES(INTERVAL) KTY_81_210_TAB[INTERVAL][2]
#define INTERVAL_MAX_RES(INTERVAL) KTY_81_210_TAB[INTERVAL][3]

extern short ADC_AVG_VALUE;
extern const float KTY_81_210_TAB[24][4];
void adcInit();
void analogInputInit();
void startConversion();
void printADC();

#endif