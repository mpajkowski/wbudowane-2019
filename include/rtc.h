#ifndef _RTC_H
#define _RTC_H

#include <stm32f3xx_ll_rtc.h>
#include <stm32f3xx_ll_rcc.h>
#include "stm32f3xx_ll_pwr.h"
#include <stm32f3xx_ll_bus.h>

void LSIinit();
void RTCinit();
void setTimeStampBuffer(char *time_buffer);

#endif //_RTC_H