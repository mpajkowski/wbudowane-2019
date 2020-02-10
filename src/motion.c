#include "motion.h"
#include "led.h"
#include "rtc.h"
#include "serial.h"
#include "trace.h"
#include "utils.h"
#include <stm32f3xx_ll_exti.h>

static char* FORMAT_STR = "+DATABEGIN+%s;%s+DATAEND+\r\n";
#define BUFSIZE 100
static char buf[BUFSIZE] = {};

void motionInit()
{
    ENABLE_CLOCK_MOTION_GPIO;

    LL_GPIO_InitTypeDef gpio = {
        .Pin = MOTION_STATE,
        .Mode = LL_GPIO_MODE_INPUT,
    };

    LL_GPIO_Init(MOTION_PORT, &gpio);

    LL_EXTI_InitTypeDef exti = {
        .Line_0_31 = LL_EXTI_LINE_3,
        .Mode = LL_EXTI_MODE_IT,
        .Trigger = LL_EXTI_TRIGGER_RISING_FALLING,
        .LineCommand = ENABLE,
    };
    LL_EXTI_Init(&exti);

    NVIC_EnableIRQ(EXTI3_IRQn);
}

void EXTI3_IRQHandler()
{
    static int cnt;
    if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_3)) {
        if (LL_GPIO_IsInputPinSet(MOTION_PORT, MOTION_STATE)) {
            LL_GPIO_SetOutputPin(LED_PORT, LED_ALL_PINS);
            TRACE_DEBUG("MOTION HIGH! Counter: %d", ++cnt);

            char* date = getDate();
            char* time = getTime();

            snprintf(buf, BUFSIZE, FORMAT_STR, date ? date : "NULL", time);
            serialPuts(buf);
        } else {
            LL_GPIO_ResetOutputPin(LED_PORT, LED_ALL_PINS);
            TRACE_DEBUG("MOTION LOW");
        }

        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_3);
    }
}
