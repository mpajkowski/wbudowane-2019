#include "rtc.h"

void HSEinit(){
    LL_RCC_HSE_Enable();
    int HSEStartUpStatus = LL_RCC_HSE_IsReady();

    while(HSEStartUpStatus == RESET){
        HSEStartUpStatus = LL_RCC_HSE_IsReady();
    }
    // if(LL_RCC_HSE_IsReady()){}
}

void LSIinit(){
    LL_RCC_LSI_Enable();

    volatile u_int32_t is_LSI_ready = LL_RCC_LSI_IsReady();
    while(is_LSI_ready != 1){ 
        is_LSI_ready = LL_RCC_LSI_IsReady();
        // wait unitil LSI is ready
    }
}

void RTCinit(){
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
    LL_PWR_EnableBkUpAccess();

    LL_RCC_ForceBackupDomainReset();
    LL_RCC_ReleaseBackupDomainReset();

    LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_HSE_DIV32);

    LL_RCC_EnableRTC();
    
    LL_RTC_DisableWriteProtection(RTC);
    if (LL_RTC_EnterInitMode(RTC) != SUCCESS)   
    {
       return;
    }

    int rtc_error = LL_RCC_IsEnabledRTC();
    while(rtc_error != 1){
        rtc_error = LL_RCC_IsEnabledRTC();
    }

    LL_RTC_SetHourFormat(RTC, LL_RTC_HOURFORMAT_24HOUR);

    uint32_t clock_src = LL_RCC_GetRTCClockSource();

    if(clock_src == LL_RCC_RTC_CLKSOURCE_HSE_DIV32){
        LL_RTC_SetAsynchPrescaler(RTC, RTC_ASYNCH_PREDIV_HSE);
        LL_RTC_SetSynchPrescaler(RTC, RTC_SYNCH_PREDIV_HSE);
    }
    else if(clock_src == LL_RCC_RTC_CLKSOURCE_LSI){
        LL_RTC_SetAsynchPrescaler(RTC, RTC_ASYNCH_PREDIV_LSI);
        LL_RTC_SetSynchPrescaler(RTC, RTC_SYNCH_PREDIV_LSI);
    }
    else{
        LL_RTC_EnableWriteProtection(RTC);
        LL_PWR_DisableBkUpAccess();
        return;
    }

    if (LL_RTC_ExitInitMode(RTC) != 1)   
    {
         LL_RTC_EnableWriteProtection(RTC);
         LL_PWR_DisableBkUpAccess();
         return;
    }

    LL_RTC_EnableWriteProtection(RTC);
    LL_PWR_DisableBkUpAccess();
}

void getTimeStampBuffer(char *time_buffer){
    volatile uint32_t seconds = LL_RTC_TIME_GetSecond(RTC);
    volatile unsigned short seconds_bin = __LL_RTC_CONVERT_BCD2BIN(seconds);

    volatile uint32_t minutes = LL_RTC_TIME_GetMinute(RTC);
    volatile unsigned short minutes_bin = __LL_RTC_CONVERT_BCD2BIN(minutes);

    volatile uint32_t hours = LL_RTC_TIME_GetHour(RTC);
    volatile unsigned short hours_bin = __LL_RTC_CONVERT_BCD2BIN(hours);

    sprintf(time_buffer, "%hu:%hu:%hu", hours_bin, minutes_bin, seconds_bin);
}

void getDateStampBuffer(char *time_buffer){
    volatile uint32_t days = LL_RTC_DATE_GetDay(RTC);
    volatile unsigned short days_bin = __LL_RTC_CONVERT_BCD2BIN(days);

    volatile uint32_t months = LL_RTC_DATE_GetMonth(RTC);
    volatile unsigned short months_bin = __LL_RTC_CONVERT_BCD2BIN(months);

    volatile uint32_t years = LL_RTC_DATE_GetYear(RTC);
    volatile unsigned short years_bin = __LL_RTC_CONVERT_BCD2BIN(years);
    years_bin += 2000;
    sprintf(time_buffer, "%hu.%hu.%hu", days_bin, months_bin, years_bin);
}

void setTime(int seconds, int minutes, int hours){
    LL_PWR_EnableBkUpAccess();    
    LL_RTC_DisableWriteProtection(RTC);
    if (LL_RTC_EnterInitMode(RTC) != SUCCESS)   
    {
       return;
    }

    int rtc_error = LL_RCC_IsEnabledRTC();
    while(rtc_error != 1){
        rtc_error = LL_RCC_IsEnabledRTC();
    }

    LL_RTC_TimeTypeDef initTime = {
        .TimeFormat = LL_RTC_HOURFORMAT_24HOUR,
        .Hours = hours,
        .Minutes = minutes,
        .Seconds = seconds
        };

    LL_RTC_TIME_Init(RTC, LL_RTC_FORMAT_BIN, &initTime);
    
    if (LL_RTC_ExitInitMode(RTC) != 1)   
    {
         LL_RTC_EnableWriteProtection(RTC);
         LL_PWR_DisableBkUpAccess();
         return;
    }

    LL_RTC_EnableWriteProtection(RTC);
    LL_PWR_DisableBkUpAccess();
}

void setDate(uint8_t weekDay, int days, int months, int years){
    LL_PWR_EnableBkUpAccess();    
    LL_RTC_DisableWriteProtection(RTC);
    if (LL_RTC_EnterInitMode(RTC) != SUCCESS)   
    {
       return;
    }

    int rtc_error = LL_RCC_IsEnabledRTC();
    while(rtc_error != 1){
        rtc_error = LL_RCC_IsEnabledRTC();
    }

    LL_RTC_DateTypeDef initDate = {
        .WeekDay = weekDay,
        .Month = months,
        .Day = days,
        .Year = years
        };

    LL_RTC_DATE_Init(RTC, LL_RTC_FORMAT_BIN, &initDate);
    
    if (LL_RTC_ExitInitMode(RTC) != 1)   
    {
         LL_RTC_EnableWriteProtection(RTC);
         LL_PWR_DisableBkUpAccess();
         return;
    }

    LL_RTC_EnableWriteProtection(RTC);
    LL_PWR_DisableBkUpAccess();
}
