///
///  STM32F3 Discovery (aka. Target) to LEDs (internal)
///
///  |-------------|-----|-----|------|------|------|------|------|------|
///  | LED no.     | (1) | (2) | (3)  | (4)  | (5)  | (6)  | (7)  | (8)  |
///  |-------------|-----|-----|------|------|------|------|------|------|
///  | Target PIN  | PA8 | PA9 | PA10 | PA11 | PA12 | PA13 | PA14 | PA15 |
///  |-------------|-----|-----|------|------|------|------|------|------|
///

#ifndef _LED_H
#define _LED_H

#include <stdint.h>

#include <stm32f3xx_ll_bus.h>
#include <stm32f3xx_ll_gpio.h>
#include <stm32f3xx_ll_rcc.h>

#define ENABLE_CLOCK_LED_GPIO LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOE)

#define LED_PORT GPIOE
#define LED1_PIN LL_GPIO_PIN_8
#define LED2_PIN LL_GPIO_PIN_9
#define LED3_PIN LL_GPIO_PIN_10
#define LED4_PIN LL_GPIO_PIN_11
#define LED5_PIN LL_GPIO_PIN_12
#define LED6_PIN LL_GPIO_PIN_13
#define LED7_PIN LL_GPIO_PIN_14
#define LED8_PIN LL_GPIO_PIN_15
#define LED_ALL_PINS                                                                               \
    LED1_PIN | LED2_PIN | LED3_PIN | LED4_PIN | LED5_PIN | LED6_PIN | LED7_PIN | LED8_PIN
#define LEDS_N 8

void ledInit();
void led1ToggleCycle();
void led2ToggleCycle();
void led3ToggleCycle();
void led4ToggleCycle();
void led5ToggleCycle();
void led6ToggleCycle();
void led7ToggleCycle();
void led8ToggleCycle();
void ledAllToggleCycle();
void ledWindMillToggleCycle();

#endif