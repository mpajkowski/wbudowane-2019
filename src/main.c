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
    delay(10000);
    ledInit();
    displayInit();
    // motionInit();
    serialInit();
    buttonInit();

    displayClearBuf();
    displayPuts(1, 2, "Initializing...", 1);

    rtcInit();

    setOneSecondAlarm();
    enableAlarmAInterrupt();
    displayClearBuf();

    setTime(23, 59, 40);
    setDate(1, 1, 1, 19);
    
    analogInputInit();
    adcInit();
    startConversion();

    // while (1) {
    //     delay(1000000);
    //     displayClearBuf();
    //     printADC();
    // }
}