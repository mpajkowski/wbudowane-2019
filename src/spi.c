#include "spi.h"

void spiSend(SPI_TypeDef* spi, uint8_t byte)
{
    while (!LL_SPI_IsActiveFlag_TXE(spi))
        ;

    LL_SPI_TransmitData8(spi, byte);

    while (LL_I2S_IsActiveFlag_BSY(spi))
        ;
}