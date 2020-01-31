#ifndef _ADC_H
#define _ADC_H

#include <stm32f3xx_ll_adc.h>
#include <stm32f3xx_ll_gpio.h>
#include <stm32f3xx_ll_rcc.h>
#include <led.h>
#include <display.h>

#define ENABLE_TEMPERATURE_INPUT_GPIO LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA)
#define TEMPERATURE_PORT GPIOC
#define TEMPERATURE_PIN LL_GPIO_PIN_2


void adcInit();
void analogInputInit();
#endif