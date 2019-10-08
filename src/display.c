#include "display.h"

static void spiSend(uint8_t byte)
{
    while (!LL_SPI_IsActiveFlag_TXE(DISPLAY_SPI))
        ;

    LL_SPI_TransmitData8(DISPLAY_SPI, byte);

    while (LL_I2S_IsActiveFlag_BSY(DISPLAY_SPI))
        ;
}

inline static void gpioInit()
{
    ENABLE_CLOCK_DISPLAY_GPIO;

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
}

inline static void spiInit()
{
    ENABLE_CLOCK_DISPLAY_SPI;

    LL_SPI_InitTypeDef spiInit = {
        .Mode = SPI_MODE_MASTER,
        .NSS = SPI_NSS_SOFT,
        .BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV16,
        .DataWidth = LL_SPI_DATAWIDTH_8BIT,
    };

    LL_SPI_Init(DISPLAY_SPI, &spiInit);
    LL_SPI_Enable(DISPLAY_SPI);
}

void displayReset()
{
    LL_GPIO_ResetOutputPin(DISPLAY_PORT, DISPLAY_RST);
    LL_GPIO_SetOutputPin(DISPLAY_PORT, DISPLAY_RST);
}

void displaySendCommand(uint8_t command)
{
    LL_GPIO_ResetOutputPin(DISPLAY_PORT, DISPLAY_CE | DISPLAY_DC);
    spiSend(command);
    LL_GPIO_SetOutputPin(DISPLAY_PORT, DISPLAY_CE);
}

void displaySendData(const uint8_t* data, int size)
{
    LL_GPIO_SetOutputPin(DISPLAY_PORT, DISPLAY_DC);
    LL_GPIO_ResetOutputPin(DISPLAY_PORT, DISPLAY_CE);

    for (int i = 0; i < size; ++i) {
        spiSend(data[i]);
    }

    LL_GPIO_SetOutputPin(DISPLAY_PORT, DISPLAY_CE);
}

void displayInit()
{
    gpioInit();
    spiInit();

    displayReset();
    displaySendCommand(0x21);
    displaySendCommand(0x14);
    displaySendCommand(0x80 | 0x2f);
    displaySendCommand(0x20);
    displaySendCommand(0x0c);
}

void displayTest()
{
    displaySendData(logo_mini_mono, sizeof(logo_mini_mono));
}