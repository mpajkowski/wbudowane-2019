#ifndef _RTC_H
#define _RTC_H

#define RTC_ASYNCH_PREDIV_HSE ((uint32_t)0x7C)
#define RTC_SYNCH_PREDIV_HSE ((uint32_t)0x7CF)

#include "display.h"
#include "stm32f3xx_ll_pwr.h"
#include <stm32f3xx_ll_bus.h>
#include <stm32f3xx_ll_exti.h>
#include <stm32f3xx_ll_rcc.h>
#include <stm32f3xx_ll_rtc.h>

void rtcInit();
char* getTime();
char* getDate();
void setTime(int hours, int minutes, int seconds);
void setDate(uint8_t weekDay, int days, int months, int years);
void setOneSecondAlarm();
void RTC_Alarm_IRQHandler(void);
void enableAlarmAInterrupt();

#endif //_RTC_H