#include "led.h"
#include "utils.h"

void ledInit()
{
    ENABLE_CLOCK_LED_GPIO;

    LL_GPIO_InitTypeDef gpioInitStruct = {
        .Pin = LED_ALL_PINS,
        .Mode = LL_GPIO_MODE_OUTPUT,
        .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
    };

    LL_GPIO_Init(LED_PORT, &gpioInitStruct);
}

void led1ToggleCycle()
{
    LL_GPIO_SetOutputPin(LED_PORT, LED1_PIN);
    delay(1000000);
    LL_GPIO_ResetOutputPin(LED_PORT, LED1_PIN);
    delay(1000000);
}