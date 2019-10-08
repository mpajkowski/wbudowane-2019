#include "utils.h"

void delay(uint32_t us)
{
    while (us--) {
        asm volatile("nop");
    }
}