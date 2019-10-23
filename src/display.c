#include "display.h"
#include "font.h"
#include <string.h>

uint8_t DISPLAY_BUFFER[DISPLAY_BUFSIZE] = {};

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

    // Init sequence
    displayReset();                      // reset
    displaySendCommand(1 << 5 | 1);      // extended command mode
    displaySendCommand(1 << 7 | 0x36);   // set contrast (vop)
    displaySendCommand(1 << 2);          // set temperature coefficient
    displaySendCommand(1 << 4 | 1 << 2); // set bias command
    displaySendCommand(1 << 5);          // basic command mode
    displaySendCommand(1 << 3 | 1 << 2); // normal display mode
}

static void newline(uint8_t** buf, uint8_t* carretPos)
{
    *buf += DISPLAY_WIDTH - *carretPos * FONT_WIDTH;
    *carretPos = 0;
}

void displayPuts(size_t startX, size_t startY, const char* str, uint8_t clearBuf)
{
    if (clearBuf) {
        displayClearBuf();
    }

    uint8_t carretPos = startX * FONT_WIDTH;
    uint8_t* buf = &DISPLAY_BUFFER[startY * DISPLAY_WIDTH + carretPos];

    while (*str) {
        uint8_t character = *str++;

        if (character == '\n') {
            newline(&buf, &carretPos);
        } else {
            if (carretPos == DISPLAY_WIDTH / FONT_WIDTH) {
                newline(&buf, &carretPos);
            }

            memcpy(buf, font_ASCII[character - ' '], FONT_WIDTH);

            buf += FONT_WIDTH;
            carretPos++;
        }
    }

    *buf = 0;

    displaySendData(DISPLAY_BUFFER, DISPLAY_BUFSIZE);
}

void displayClearBuf()
{
    memset(DISPLAY_BUFFER, 0, DISPLAY_BUFSIZE);
}
