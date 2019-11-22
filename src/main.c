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
    led1ToggleCycle();

    char time_buffer[50] = {0};

    setTime(15, 5, 4);
    setDate(1, 22, 11, 19);

    while(1){
        getDateStampBuffer(time_buffer);
        displayPuts(0, 0, time_buffer, 1);
        getTimeStampBuffer(time_buffer);
        displayPuts(0, 1, time_buffer, 0);
    }
}