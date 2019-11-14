#include "button.h"
#include "led.h"
#include "utils.h"
#include <stm32f3xx_ll_exti.h>

void buttonInit()
{
    ENABLE_CLOCK_BUTTON_GPIO;

    LL_GPIO_InitTypeDef gpio = {
        .Pin = BUTTON_STATE,
        .Mode = LL_GPIO_MODE_INPUT,
        .Speed = LL_GPIO_SPEED_FREQ_HIGH,
        .Pull = LL_GPIO_PULL_DOWN,
    };

    LL_GPIO_Init(BUTTON_PORT, &gpio);

    LL_EXTI_InitTypeDef exti = {
        .Line_0_31 = LL_EXTI_LINE_0,
        .Mode = LL_EXTI_MODE_IT,
        .Trigger = LL_EXTI_TRIGGER_RISING_FALLING,
        .LineCommand = ENABLE,
    };
    
    LL_EXTI_Init(&exti);

    NVIC_EnableIRQ(EXTI0_IRQn);
}

void EXTI0_IRQHandler()
{
    if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_0)) {
        if (LL_GPIO_IsInputPinSet(BUTTON_PORT, BUTTON_STATE)) {
            LL_GPIO_SetOutputPin(LED_PORT, LED_ALL_PINS);
        } else {
            LL_GPIO_ResetOutputPin(LED_PORT, LED_ALL_PINS);
        }
    }

    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_0);
}
