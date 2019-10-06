#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>

void delay(uint32_t us)
{
    while (us--) {
        asm volatile ("nop");
    }
}

int main()
{
    RCC_DeInit();
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);

    GPIO_InitTypeDef gpioInit = {
        .GPIO_Pin = GPIO_Pin_8, 
        .GPIO_Mode = GPIO_Mode_OUT,
        .GPIO_OType = GPIO_OType_PP,
    };

    GPIO_Init(GPIOE, &gpioInit);

    for (;;) {
        GPIO_SetBits(GPIOE, GPIO_Pin_8);
        delay(100000);
        GPIO_ResetBits(GPIOE, GPIO_Pin_8);
        delay(100000);
    }

    return 0;
}