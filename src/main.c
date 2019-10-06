#include "constants.h"
#include "utils.h"
#include <stm32f3xx_ll_bus.h>
#include <stm32f3xx_ll_rcc.h>

void initLeds()
{
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOE);

    uint32_t allLeds = 0;
    for (size_t i = 0; i < LEDS_N; i++) {
        allLeds |= LEDS[i];
    }

    LL_GPIO_InitTypeDef gpioInitStruct = {
        .Pin = allLeds,
        .Mode = LL_GPIO_MODE_OUTPUT,
        .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
    };

    LL_GPIO_Init(GPIOE, &gpioInitStruct);
}

int main()
{
    LL_RCC_DeInit();
    initLeds();

    for (;;) {
        for (size_t i = 0; i < LEDS_N; i++) {
            uint32_t currentLed = LEDS[i];

            LL_GPIO_SetOutputPin(GPIOE, currentLed);
            delay(100000);
            LL_GPIO_ResetOutputPin(GPIOE, currentLed);
            delay(100000);
        }
    }

    return 0;
}