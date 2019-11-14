#include "display.h"
#include "led.h"
#include "motion.h"
#include "serial.h"
#include "utils.h"
#include "button.h"

int main()
{
    ledInit();
    displayInit();
    motionInit();
    serialInit();
    buttonInit();

    const char lorem[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed vehicula "
                         "sodales nisl eu aliquet.";

    displayClearBuf();
    displayPuts(0, 0, lorem, 0);

    led1ToggleCycle();
}