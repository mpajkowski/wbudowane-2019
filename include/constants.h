#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#include <stm32f3xx_ll_gpio.h>

#define LED1_PIN LL_GPIO_PIN_8
#define LED2_PIN LL_GPIO_PIN_9
#define LED3_PIN LL_GPIO_PIN_10
#define LED4_PIN LL_GPIO_PIN_11
#define LED5_PIN LL_GPIO_PIN_12
#define LED6_PIN LL_GPIO_PIN_13
#define LED7_PIN LL_GPIO_PIN_14
#define LED8_PIN LL_GPIO_PIN_15
#define LEDS_N 8

uint32_t const LEDS[] = { LED1_PIN, LED2_PIN, LED3_PIN, LED4_PIN,
                          LED5_PIN, LED6_PIN, LED7_PIN, LED8_PIN };

#endif