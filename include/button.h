#ifndef _BUTTON_H
#define _BUTTON_H
#include <stm32f3xx_ll_gpio.h>

#define ENABLE_CLOCK_BUTTON_GPIO LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA)
#define BUTTON_PORT GPIOA
#define BUTTON_STATE LL_GPIO_PIN_0

void buttonInit();
void EXTI0_IRQHandler();
#endif //_BUTTON_H