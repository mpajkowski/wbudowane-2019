#include "display.h"
#include "led.h"
#include "motion.h"
#include "uart.h"
#include "utils.h"

int main()
{
    LL_RCC_DeInit();
    ledInit();
    displayInit();
    motionInit();

    const char lorem[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed vehicula "
                         "sodales nisl eu aliquet.";

    displayClearBuf();
    displayPuts(0, 0, lorem, 0);
    uartInit();

    led1ToggleCycle();
}