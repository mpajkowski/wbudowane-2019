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

void led2ToggleCycle(){
    LL_GPIO_SetOutputPin(LED_PORT, LED2_PIN);
    delay(1000000);
    LL_GPIO_ResetOutputPin(LED_PORT, LED2_PIN);
    delay(1000000);
}

void led3ToggleCycle(){
    LL_GPIO_SetOutputPin(LED_PORT, LED3_PIN);
    delay(1000000);
    LL_GPIO_ResetOutputPin(LED_PORT, LED3_PIN);
    delay(1000000);
}
void led4ToggleCycle(){
    LL_GPIO_SetOutputPin(LED_PORT, LED4_PIN);
    delay(1000000);
    LL_GPIO_ResetOutputPin(LED_PORT, LED4_PIN);
    delay(1000000);
}
void led5ToggleCycle(){
    LL_GPIO_SetOutputPin(LED_PORT, LED5_PIN);
    delay(1000000);
    LL_GPIO_ResetOutputPin(LED_PORT, LED5_PIN);
    delay(1000000);
}
void led6ToggleCycle(){
    LL_GPIO_SetOutputPin(LED_PORT, LED6_PIN);
    delay(1000000);
    LL_GPIO_ResetOutputPin(LED_PORT, LED6_PIN);
    delay(1000000);
}
void led7ToggleCycle(){
    LL_GPIO_SetOutputPin(LED_PORT, LED7_PIN);
    delay(1000000);
    LL_GPIO_ResetOutputPin(LED_PORT, LED7_PIN);
    delay(1000000);
}
void led8ToggleCycle(){
    LL_GPIO_SetOutputPin(LED_PORT, LED8_PIN);
    delay(1000000);
    LL_GPIO_ResetOutputPin(LED_PORT, LED8_PIN);
    delay(1000000);
}

void ledAllToggleCycle(){
    LL_GPIO_SetOutputPin(LED_PORT, LED_ALL_PINS);
    delay(1000000);
    LL_GPIO_ResetOutputPin(LED_PORT, LED_ALL_PINS);
    delay(1000000);
}

void ledWindMillToggleCycle(){
    LL_GPIO_SetOutputPin(LED_PORT, LED1_PIN | LED5_PIN);
    delay(250000);
    LL_GPIO_ResetOutputPin(LED_PORT, LED1_PIN | LED5_PIN);

    LL_GPIO_SetOutputPin(LED_PORT, LED2_PIN | LED6_PIN);
    delay(250000);
    LL_GPIO_ResetOutputPin(LED_PORT, LED2_PIN | LED6_PIN);

    LL_GPIO_SetOutputPin(LED_PORT, LED3_PIN | LED7_PIN);
    delay(250000);
    LL_GPIO_ResetOutputPin(LED_PORT, LED3_PIN | LED7_PIN);

    LL_GPIO_SetOutputPin(LED_PORT, LED4_PIN | LED8_PIN);
    delay(250000);
    LL_GPIO_ResetOutputPin(LED_PORT, LED4_PIN | LED8_PIN);
}