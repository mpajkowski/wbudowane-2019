#include "adc.h"
#include "button.h"
#include "display.h"
#include "led.h"
#include "motion.h"
#include "rtc.h"
#include "serial.h"
#include "string.h"
#include "utils.h"
int main()
{
    ledInit();
    displayInit();
    motionInit();
    serialInit();
    buttonInit();

    displayClearBuf();
    displayPuts(1, 2, "Initializing...", 1);

    rtcInit();

    setOneSecondAlarm();
    enableAlarmAInterrupt();
    displayClearBuf();

    setTime(23, 59, 40);
    setDate(5, 6, 2, 20);
    
    analogInputInit();
    adcInit();
    startConversion();
}