///
///  STM32F3 Discovery (aka. Target) to Bluetooth HC-05 (aka. Serial) (external)
///
///  |-----------------|-----|-----|------|-----|
///  | Serial PIN no.  | (1) | (2) | (3)  | (4) |
///  |-----------------|-----|-----|------|-----|
///  | Serial PIN fun. | VCC | GND | TX   | RX  |
///  |-----------------|-----|-----|------|-----|
///  | Target PIN      | +3V | GND | PA10 | PA9 |
///  |-----------------|-----|-----|------|-----|
///

#ifndef _SERIAL_H
#define _SERIAL_H

#include <stm32f3xx_ll_gpio.h>
#include <stm32f3xx_ll_usart.h>

#define ENABLE_CLOCK_UART_GPIO LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA)
#define ENABLE_CLOCK_UART1 LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
#define SERIAL_TX LL_GPIO_PIN_9
#define SERIAL_RX LL_GPIO_PIN_10
#define SERIAL_PORT GPIOA
#define SERIAL_BAUDRATE 9600
#define SERIAL_UART USART1

void serialInit();
void serialPutc(char);
void serialPuts(const char*);

// IRQ callbacks
void USART1_IRQHandler();

#endif // _SERIAL_H