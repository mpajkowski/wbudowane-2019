#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#include <stm32f3xx_ll_bus.h>
#include <stm32f3xx_ll_gpio.h>
#include <stm32f3xx_ll_rcc.h>
#include <stm32f3xx_ll_spi.h>

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

static uint32_t const LEDS[] = { LED1_PIN, LED2_PIN, LED3_PIN, LED4_PIN,
                                 LED5_PIN, LED6_PIN, LED7_PIN, LED8_PIN };

/*
    STM32F3 Discovery (aka. Target) to Nokia 5110 display (aka. Display)

    |-------------------|-----|-----|-----|-----|-----|------|-----|-----|
    | Display PIN no.   | (1) | (2) | (3) | (4) | (5) | (6)  | (7) | (8) |
    |-------------------|-----|-----|-----|-----|-----|------|-----|-----|
    | Display PIN fun.  | RST | CE  | DC  | DIN | CLK | VCC  | BL  | GND |
    |-------------------|-----|-----|-----|-----|-----|------|-----|-----|
    | Target PIN        | PA0 | PA4 | PA1 | PA7 | PA5 | 3.3V | PA2 | GND |
    |-------------------|-----|-----|-----|-----|-----|------|-----|-----|

    SPI notes:
        * (2) CE -> PA4 - SPI1_NSS
        * (4) DIN -> PA7 - SPI1_MOSI
        * (5) CLK -> PA5 - SPI1_SCK
*/
#define DISPLAY_PORT GPIOA
#define DISPLAY_SPI SPI1

#define ENABLE_CLOCK_DISPLAY_GPIO LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA)
#define ENABLE_CLOCK_DISPLAY_SPI LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI1)

#define DISPLAY_RST LL_GPIO_PIN_0
#define DISPLAY_CE LL_GPIO_PIN_4
#define DISPLAY_DC LL_GPIO_PIN_1
#define DISPLAY_DIN LL_GPIO_PIN_7
#define DISPLAY_CLK LL_GPIO_PIN_5
#define DISPLAY_BL LL_GPIO_PIN_2

#define DISPLAY_ALL DISPLAY_RST | DISPLAY_CE | DISPLAY_DC | DISPLAY_DIN | DISPLAY_CLK | DISPLAY_BL

#endif