#ifndef _UTILS_H
#define _UTILS_H

#include <stdio.h>

#define DELAY(X)                                                                                   \
    do {                                                                                           \
        for (uint32_t i = 0; i < X; i++) {                                                         \
            asm volatile("nop");                                                                   \
        }                                                                                          \
    } while (0);

#endif // _UTILS_H