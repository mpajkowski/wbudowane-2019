#include "uart.h"
#include "utils.h"
#include <stm32f3xx_ll_bus.h>
#include <stm32f3xx_ll_rcc.h>

void uartInit()
{
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);

    LL_GPIO_InitTypeDef gpioInit = {
        .Pin = UART_TX | UART_RX,
        .Mode = LL_GPIO_MODE_ALTERNATE,
        .Speed = LL_GPIO_SPEED_FREQ_HIGH,
        .Alternate = LL_GPIO_AF_7,
        .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
        .Pull = LL_GPIO_PULL_UP,
    };

    LL_USART_InitTypeDef uartInit = {};
    uartInit.BaudRate = UART_BAUDRATE;
    uartInit.BaudRate = 9600;
    uartInit.DataWidth = LL_USART_DATAWIDTH_8B;
    uartInit.Parity = LL_USART_PARITY_NONE;
    uartInit.TransferDirection = LL_USART_DIRECTION_TX_RX;

    LL_GPIO_Init(UART_PORT, &gpioInit);

    LL_USART_Init(UART_HANDLE, &uartInit);
    LL_USART_Enable(UART_HANDLE);

    while ((!(LL_USART_IsActiveFlag_TEACK(UART_HANDLE))) ||
           (!(LL_USART_IsActiveFlag_REACK(UART_HANDLE)))) {
    }
}

void uartPutc(char ch)
{
    while (!LL_USART_IsActiveFlag_TXE(UART_HANDLE))
        ;

    LL_USART_TransmitData8(UART_HANDLE, ch);
}

void uartPuts(const char* str)
{
    while (*str) {
        uartPutc(*str++);
    }
}