#include "display.h"
#include "led.h"
#include "motion.h"
#include "serial.h"
#include "utils.h"
#include "button.h"
#include "rtc.h"

int main()
{
    ledInit();
    displayInit();
    motionInit();
    serialInit();
    buttonInit();
    
    HSEinit();
    LSIinit();
    RTCinit();

    const char lorem[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed vehicula "
                         "sodales nisl eu aliquet.";

    displayClearBuf();
    displayPuts(0, 0, lorem, 0);

    
    ledWindMillToggleCycle();
    
    setTime(15, 5, 4);
    setDate(1, 1, 1, 19);
    setOneSecondAlarm();
    enableAlarmAInterrupt();
}