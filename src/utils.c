#include "utils.h"

void delay(uint32_t us)
{
    // FIXME use timer
    while (us--) {
        asm volatile("nop");
    }
}