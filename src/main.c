#include "display.h"
#include "led.h"
#include "utils.h"

int main()
{
    LL_RCC_DeInit();
    ledInit();
    displayInit();

    displayTest();
    led1ToggleCycle();

    return 0;
}