#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#include <stm32f30x_gpio.h>

#define LED1_PIN GPIO_Pin_8
#define LED2_PIN GPIO_Pin_9
#define LED3_PIN GPIO_Pin_10
#define LED4_PIN GPIO_Pin_11
#define LED5_PIN GPIO_Pin_12
#define LED6_PIN GPIO_Pin_13
#define LED7_PIN GPIO_Pin_14
#define LED8_PIN GPIO_Pin_15

uint32_t const LEDS[] = { LED1_PIN, LED2_PIN, LED3_PIN, LED4_PIN,
                          LED5_PIN, LED6_PIN, LED7_PIN, LED8_PIN };

#endif