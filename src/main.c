#include "constants.h"
#include "utils.h"
#include <stm32f30x_rcc.h>

void initLeds()
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);

    uint32_t allLeds = 0;
    for (size_t i = 0; i < LEDS_N; i++) {
        allLeds |= LEDS[i];
    }

    GPIO_InitTypeDef gpioInitStruct = {
        .GPIO_Pin = allLeds,
        .GPIO_Mode = GPIO_Mode_OUT,
        .GPIO_OType = GPIO_OType_PP,
    };

    GPIO_Init(GPIOE, &gpioInitStruct);
}

int main()
{
    RCC_DeInit();
    initLeds();

    for (;;) {
        for (size_t i = 0; i < LEDS_N; i++) {
            uint32_t currentLed = LEDS[i];

            GPIO_SetBits(GPIOE, currentLed);
            delay(100000);
            GPIO_ResetBits(GPIOE, currentLed);
            delay(100000);
        }
    }

    return 0;
}