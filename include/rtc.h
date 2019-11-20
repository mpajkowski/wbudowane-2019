#ifndef _RTC_H
#define _RTC_H

#define RTC_ASYNCH_PREDIV_LSI          ((uint32_t)0x7C)
#define RTC_SYNCH_PREDIV_LSI           ((uint32_t)0x0127)

#include <stm32f3xx_ll_rtc.h>
#include <stm32f3xx_ll_rcc.h>
#include "stm32f3xx_ll_pwr.h"
#include <stm32f3xx_ll_bus.h>

void HSEinit();
void LSIinit();
void RTCinit();
void setTimeStampBuffer(char *time_buffer);

#endif //_RTC_H