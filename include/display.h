///
///  STM32F3 Discovery (aka. Target) to Nokia 5110 display (aka. Display)
///
///  |-------------------|-----|-----|-----|-----|-----|------|-----|-----|
///  | Display PIN no.   | (1) | (2) | (3) | (4) | (5) | (6)  | (7) | (8) |
///  |-------------------|-----|-----|-----|-----|-----|------|-----|-----|
///  | Display PIN fun.  | RST | CE  | DC  | DIN | CLK | VCC  | BL  | GND |
///  |-------------------|-----|-----|-----|-----|-----|------|-----|-----|
///  | Target PIN        | PA0 | PA4 | PA1 | PA7 | PA5 | 3.3V | PA2 | GND |
///  |-------------------|-----|-----|-----|-----|-----|------|-----|-----|
///
///  SPI notes:
///      * (2) CE -> PA4 - SPI1_NSS
///      * (4) DIN -> PA7 - SPI1_MOSI
///      * (5) CLK -> PA5 - SPI1_SCK
///

#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <stdint.h>

#include <stm32f3xx_ll_bus.h>
#include <stm32f3xx_ll_gpio.h>
#include <stm32f3xx_ll_rcc.h>
#include <stm32f3xx_ll_spi.h>

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

#define DISPLAY_WIDTH 84
#define DISPLAY_HEIGHT 48
#define DISPLAY_BUFSIZE (DISPLAY_WIDTH * DISPLAY_HEIGHT / 8)

void displayInit();
void displayReset();
void displaySendCommand(uint8_t command);
void displaySendData(const uint8_t* data, int size);
void displayClearBuf();
void displayPuts(size_t startX, size_t startY, const char* str, uint8_t clearBuf);

#endif