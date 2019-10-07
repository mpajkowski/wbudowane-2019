#include "constants.h"
#include "utils.h"

void initLeds()
{
    ENABLE_CLOCK_LED;

    LL_GPIO_InitTypeDef gpioInitStruct = {
        .Pin = LED_ALL_PINS,
        .Mode = LL_GPIO_MODE_OUTPUT,
        .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
    };

    LL_GPIO_Init(LED_PORT, &gpioInitStruct);
}

void initDisplay()
{
    ENABLE_CLOCK_DISPLAY;

    LL_GPIO_InitTypeDef gpioInitStruct = {
        .Pin = DISPLAY_BACKLIGHT_PIN,
        .Mode = LL_GPIO_MODE_OUTPUT,
        .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
    };

    LL_GPIO_Init(DISPLAY_PORT, &gpioInitStruct);
    LL_GPIO_SetOutputPin(DISPLAY_PORT, DISPLAY_BACKLIGHT_PIN);
}

int main()
{
    LL_RCC_DeInit();
    initDisplay();

    return 0;
}