#include "rtc.h"

void HSEinit(){
    LL_RCC_HSE_Enable();
    int HSEStartUpStatus = LL_RCC_HSE_IsReady();

    while(HSEStartUpStatus != 1){
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

    // If LSI not set, set it as RTC clock source
    if (LL_RCC_GetRTCClockSource() != LL_RCC_RTC_CLKSOURCE_LSI)
    {
        LL_RCC_ForceBackupDomainReset();
        LL_RCC_ReleaseBackupDomainReset();
        LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_LSI);
    }

    LL_RCC_EnableRTC();
    LL_RTC_DisableWriteProtection(RTC);

    if (LL_RTC_EnterInitMode(RTC) != SUCCESS)   
    {
       return;
    }

    int rtc_error = LL_RCC_IsEnabledRTC();
    while(LL_RCC_IsEnabledRTC() != 1){
        rtc_error = LL_RCC_IsEnabledRTC();
    }

    LL_RTC_SetHourFormat(RTC, LL_RTC_HOURFORMAT_24HOUR);
    LL_RTC_SetAsynchPrescaler(RTC, RTC_ASYNCH_PREDIV_LSI);
    LL_RTC_SetSynchPrescaler(RTC, RTC_SYNCH_PREDIV_LSI);

    if (LL_RTC_ExitInitMode(RTC) != SUCCESS)   
    {
         LL_RTC_EnableWriteProtection(RTC);
         return;
    }

    LL_RTC_EnableWriteProtection(RTC);
}

void setTimeStampBuffer(char *time_buffer){
    volatile uint32_t seconds = LL_RTC_TIME_GetSecond(RTC);
    volatile unsigned short seconds_bin = __LL_RTC_CONVERT_BCD2BIN(seconds);

    volatile uint32_t minutes = LL_RTC_TIME_GetMinute(RTC);
    volatile unsigned short minutes_bin = __LL_RTC_CONVERT_BCD2BIN(minutes);

    volatile uint32_t hours = LL_RTC_TIME_GetHour(RTC);
    volatile unsigned short hours_bin = __LL_RTC_CONVERT_BCD2BIN(hours);

    sprintf(time_buffer, "%hu:%hu:%hu", hours_bin, minutes_bin, seconds_bin);
}
