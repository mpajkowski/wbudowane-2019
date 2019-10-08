#include "display.h"
#include "constants.h"

static void spiSend(uint8_t byte)
{
    while (!LL_SPI_IsActiveFlag_TXE(DISPLAY_SPI))
        ;

    LL_SPI_TransmitData8(DISPLAY_SPI, byte);

    while (LL_I2S_IsActiveFlag_BSY(DISPLAY_SPI))
        ;
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
