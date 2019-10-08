#include "constants.h"
#include "display.h"
#include "utils.h"

void initLeds()
{
    ENABLE_CLOCK_LED_GPIO;

    LL_GPIO_InitTypeDef gpioInitStruct = {
        .Pin = LED_ALL_PINS,
        .Mode = LL_GPIO_MODE_OUTPUT,
        .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
    };

    LL_GPIO_Init(LED_PORT, &gpioInitStruct);
}

void initDisplay()
{
    ENABLE_CLOCK_DISPLAY_GPIO;
    ENABLE_CLOCK_DISPLAY_SPI;

    LL_GPIO_InitTypeDef gpioInitSpi = {
        .Pin = DISPLAY_DIN | DISPLAY_CLK,
        .Mode = LL_GPIO_MODE_ALTERNATE,
        .Speed = LL_GPIO_SPEED_FREQ_HIGH,
        .Alternate = LL_GPIO_AF_5,
    };

    LL_GPIO_Init(DISPLAY_PORT, &gpioInitSpi);

    LL_GPIO_InitTypeDef gpioInit = {
        .Pin = DISPLAY_BL | DISPLAY_DC | DISPLAY_CE | DISPLAY_RST,
        .Mode = LL_GPIO_MODE_OUTPUT,
    };

    LL_GPIO_Init(DISPLAY_PORT, &gpioInit);

    LL_GPIO_SetOutputPin(DISPLAY_PORT, DISPLAY_CE | DISPLAY_RST | DISPLAY_BL);

    LL_SPI_InitTypeDef spiInit = {
        .Mode = SPI_MODE_MASTER,
        .NSS = SPI_NSS_SOFT,
        .BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV16,
        .DataWidth = LL_SPI_DATAWIDTH_8BIT,
    };

    // LL_SPI_SetRxFIFOThreshold(DISPLAY_SPI, SPI_RXFIFO_THRESHOLD_QF);
    LL_SPI_Init(DISPLAY_SPI, &spiInit);
    LL_SPI_Enable(DISPLAY_SPI);
}

int main()
{
    LL_RCC_DeInit();
    initLeds();
    initDisplay();

    displayReset();
    displaySendCommand(0x21);
    displaySendCommand(0x14);
    displaySendCommand(0x80 | 0x2f);
    displaySendCommand(0x20);
    displaySendCommand(0x0c);

    displaySendData(logo_mini_mono, sizeof(logo_mini_mono));

    for (;;) {
        LL_GPIO_SetOutputPin(LED_PORT, LED1_PIN);
        delay(1000000);
        LL_GPIO_ResetOutputPin(LED_PORT, LED1_PIN);
        delay(1000000);
    }

    return 0;
}