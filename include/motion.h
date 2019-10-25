///
///  STM32F3 Discovery (aka. Target) to Motion Sensor (aka. Motion) (external)
///
///  |-------------------|-----|-----|-----|
///  | Motion PIN no.    | (1) | (2) | (3) |
///  |-------------------|-----|-----|-----|
///  | Motion PIN fun.   | GND | OUT | VCC |
///  |-------------------|-----|-----|-----|
///  | Target PIN        | GND | PA3 | +5V |
///  |-------------------|-----|-----|-----|
///

#ifndef _MOTION_H
#define _MOTION_H
#include <stm32f3xx_ll_gpio.h>

#define ENABLE_CLOCK_MOTION_GPIO LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA)
#define MOTION_PORT GPIOA
#define MOTION_STATE LL_GPIO_PIN_3

void motionInit();
void EXTI3_IRQHandler();
#endif //_MOTION_H