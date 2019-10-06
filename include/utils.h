#ifndef _UTILS_H
#define _UTILS_H

#include <stdio.h>

void delay(uint32_t us)
{
    while (us--) {
        asm volatile("nop");
    }
}

#endif // _UTILS_H