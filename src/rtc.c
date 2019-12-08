#include "rtc.h"
#include "trace.h"
// https://usermanual.wiki/Document/DM00025071.756701677/html#pfa

void hseInit()
{
    LL_RCC_HSE_Enable();

    while (LL_RCC_HSE_IsReady() == RESET)
        ;
}

void rtcInit()
{
    hseInit();

    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
    LL_PWR_EnableBkUpAccess();

    LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_HSE_DIV32);

    LL_RCC_EnableRTC();

    LL_RTC_DisableWriteProtection(RTC);

    LL_RTC_EnterInitMode(RTC);

    LL_RTC_SetAsynchPrescaler(RTC, RTC_ASYNCH_PREDIV_HSE);
    LL_RTC_SetSynchPrescaler(RTC, RTC_SYNCH_PREDIV_HSE);

    LL_RTC_ExitInitMode(RTC);
}

char* getTime()
{
    static char time_buffer[9] = {};
    volatile uint32_t seconds = LL_RTC_TIME_GetSecond(RTC);
    volatile unsigned short secondsBin = __LL_RTC_CONVERT_BCD2BIN(seconds);

    volatile uint32_t minutes = LL_RTC_TIME_GetMinute(RTC);
    volatile unsigned short minutesBin = __LL_RTC_CONVERT_BCD2BIN(minutes);

    volatile uint32_t hours = LL_RTC_TIME_GetHour(RTC);
    volatile unsigned short hoursBin = __LL_RTC_CONVERT_BCD2BIN(hours);

    sprintf(time_buffer, "%02hu:%02hu:%02hu", hoursBin, minutesBin, secondsBin);

    return time_buffer;
}

char* getDate()
{
    static char time_buffer[11] = {};
    volatile uint32_t days = LL_RTC_DATE_GetDay(RTC);
    volatile unsigned short daysBin = __LL_RTC_CONVERT_BCD2BIN(days);

    volatile uint32_t months = LL_RTC_DATE_GetMonth(RTC);
    volatile unsigned short monthsBin = __LL_RTC_CONVERT_BCD2BIN(months);

    volatile uint32_t years = LL_RTC_DATE_GetYear(RTC);
    volatile unsigned short yearsBin = __LL_RTC_CONVERT_BCD2BIN(years);
    yearsBin += 2000;
    sprintf(time_buffer, "%02hu.%02hu.%hu", daysBin, monthsBin, yearsBin);

    return time_buffer;
}

void setTime(int hours, int minutes, int seconds)
{
    LL_RTC_TimeTypeDef initTime = { .TimeFormat = LL_RTC_HOURFORMAT_24HOUR,
                                    .Hours = hours,
                                    .Minutes = minutes,
                                    .Seconds = seconds };

    LL_RTC_TIME_Init(RTC, LL_RTC_FORMAT_BIN, &initTime);
}

void setDate(uint8_t weekDay, int days, int months, int years)
{
    LL_RTC_DateTypeDef initDate = {
        .WeekDay = weekDay, .Month = months, .Day = days, .Year = years
    };

    LL_RTC_DATE_Init(RTC, LL_RTC_FORMAT_BIN, &initDate);
}

void setOneSecondAlarm()
{
    LL_RTC_ALMA_Disable(RTC);

    while (!LL_RTC_IsActiveFlag_ALRAW(RTC))
        ;

    LL_RTC_AlarmTypeDef secondsAlarm = { .AlarmMask = LL_RTC_ALMA_MASK_ALL };
    LL_RTC_ALMA_Init(RTC, LL_RTC_HOURFORMAT_24HOUR, &secondsAlarm);
    LL_RTC_DisableWriteProtection(RTC);
    LL_RTC_ALMA_Enable(RTC);
}

void enableAlarmAInterrupt()
{
    LL_RTC_EnableIT_ALRA(RTC);

    LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_17);
    LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_17);

    NVIC_SetPriority(RTC_Alarm_IRQn, 0x0F);
    NVIC_EnableIRQ(RTC_Alarm_IRQn);
}

void RTC_Alarm_IRQHandler(void)
{
    static char dateTimeBuffer[20] = {};

    if (LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_17)) {
        LL_RTC_ClearFlag_ALRA(RTC);

        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_17);

        char* date = getDate();
        char* time = getTime();

        sprintf(dateTimeBuffer, "%s\n%s", date, time);
        displayPuts(0, 0, dateTimeBuffer, 0);

        TRACE_DEBUG("Date %s, Time: %s", date, time);
    }
}