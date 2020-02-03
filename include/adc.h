#ifndef _ADC_H
#define _ADC_H

#include "utils.h"
#include <display.h>
#include <led.h>
#include <stm32f3xx_ll_adc.h>
#include <stm32f3xx_ll_gpio.h>
#include <stm32f3xx_ll_rcc.h>

#define ENABLE_TEMPERATURE_INPUT_GPIO LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA)
#define TEMPERATURE_PORT GPIOC
#define TEMPERATURE_PIN LL_GPIO_PIN_2
#define SUPPLY_VOLTAGE 3.0f
#define ADC_RESOLUTION 4095.0f
#define RE_RESISTOR 2000.0f
#define SUPPLY_VOLTAGE 3.0f
#define SAMPLES_NUMBER 1000

extern short ADC_AVG_VALUE;

void adcInit();
void analogInputInit();
void startConversion();

#endif