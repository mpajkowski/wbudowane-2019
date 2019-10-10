#ifndef _USART_H
#define _USART_H

#include <stm32f3xx_ll_gpio.h>
#include <stm32f3xx_ll_usart.h>

#define UART_TX LL_GPIO_PIN_9
#define UART_RX LL_GPIO_PIN_10
#define UART_PORT GPIOA
#define UART_BAUDRATE 38400
#define UART_HANDLE USART1

void uartInit();
void uartPutc(char);
void uartPuts(const char*);

#endif