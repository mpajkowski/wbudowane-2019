#include "utils.h"

void delay(uint32_t us)
{
    // FIXME use timer
    while (us--) {
        asm volatile("nop");
    }
}

void splitFloat(float number, int* array, unsigned int round){
    array[0] = (int)number;
    array[1] = trunc((unsigned int)((number - array[0]) * pow(10, round)));
}
