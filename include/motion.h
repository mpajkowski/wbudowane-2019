#ifndef _MOTION_H
#define _MOTION_H
#include <stm32f3xx_ll_gpio.h>

#define MOTION_PORT GPIOA
#define MOTION_STATE LL_GPIO_PIN_3

void motionInit();
void EXTI3_IRQHandler();
#endif //_MOTION_H