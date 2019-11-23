#ifndef _RTC_H
#define _RTC_H

#define RTC_ASYNCH_PREDIV_LSI          ((uint32_t)0x7C)
#define RTC_SYNCH_PREDIV_LSI           ((uint32_t)0x0127)

#define RTC_ASYNCH_PREDIV_HSE          ((uint32_t)0x7C)
#define RTC_SYNCH_PREDIV_HSE           ((uint32_t)0x7CF)

#include <stm32f3xx_ll_rtc.h>
#include <stm32f3xx_ll_rcc.h>
#include "stm32f3xx_ll_pwr.h"
#include <stm32f3xx_ll_bus.h>
#include <stm32f3xx_ll_exti.h>
#include "display.h"

void HSEinit();
void LSIinit();
void RTCinit();
char* getTime();
char* getDate();
void setTime(int seconds, int minutes, int hours);
void setDate(uint8_t weekDay, int days, int months, int years);
void setOneSecondAlarm();
void RTC_Alarm_IRQHandler(void);
void enableAlarmAInterrupt();

#endif //_RTC_H