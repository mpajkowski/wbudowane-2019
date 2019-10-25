#include "serial.h"
#include <stm32f3xx_ll_bus.h>
#include <stm32f3xx_ll_rcc.h>

void serialInit()
{
    ENABLE_CLOCK_UART_GPIO;
    ENABLE_CLOCK_UART1;

    LL_GPIO_InitTypeDef gpioInit = {
        .Pin = SERIAL_TX | SERIAL_RX,
        .Mode = LL_GPIO_MODE_ALTERNATE,
        .Speed = LL_GPIO_SPEED_FREQ_HIGH,
        .Alternate = LL_GPIO_AF_7,
        .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
        .Pull = LL_GPIO_PULL_UP,
    };

    LL_USART_InitTypeDef uartInit = {
        .BaudRate = SERIAL_BAUDRATE,
        .DataWidth = LL_USART_DATAWIDTH_8B,
        .Parity = LL_USART_PARITY_NONE,
        .TransferDirection = LL_USART_DIRECTION_TX_RX,
    };

    LL_GPIO_Init(SERIAL_PORT, &gpioInit);

    LL_USART_Init(SERIAL_UART, &uartInit);
    LL_USART_Enable(SERIAL_UART);

    while ((!(LL_USART_IsActiveFlag_TEACK(SERIAL_UART))) ||
           (!(LL_USART_IsActiveFlag_REACK(SERIAL_UART)))) {
    }

    LL_USART_EnableIT_RXNE(SERIAL_UART);
    NVIC_EnableIRQ(USART1_IRQn);
}

void serialPutc(char ch)
{
    while (!LL_USART_IsActiveFlag_TXE(SERIAL_UART))
        ;

    LL_USART_TransmitData8(SERIAL_UART, ch);
}

void serialPuts(const char* str)
{
    while (*str) {
        serialPutc(*str++);
    }
}

void USART1_IRQHandler()
{
    if (LL_USART_IsActiveFlag_RXNE(SERIAL_UART)) {
        uint8_t ch = LL_USART_ReceiveData8(SERIAL_UART);
        serialPutc(ch);
    }
}