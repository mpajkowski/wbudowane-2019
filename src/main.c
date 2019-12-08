#include "button.h"
#include "display.h"
#include "led.h"
#include "motion.h"
#include "rtc.h"
#include "serial.h"
#include "utils.h"

int main()
{
    delay(10000);
    ledInit();
    displayInit();
    motionInit();
    serialInit();
    buttonInit();

    displayClearBuf();
    displayPuts(1, 2, "Initializing...", 1);

    ledWindMillToggleCycle();

    rtcInit();

    setOneSecondAlarm();
    enableAlarmAInterrupt();
    displayClearBuf();

    setTime(23, 59, 40);
    setDate(1, 1, 1, 19);
}