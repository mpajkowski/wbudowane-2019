#include "adc.h"
#include "utils.h"
/*
In the STM32F3 Series devices, the ADC clock is derived from the PLL output. It can reach 72 MHz and
is divided by the following prescalers values programmed inside the RCC: 1, 2, 4, 6, 8,10,12,16, 32,
64, 128 or 256. It is asynchronous to the AHB clock.

Alternatively, in both STM32F3 Series and STM32G4 Series, the ADC clock is derived from the AHB
clock of the ADC bus interface, divided by a programmable factor (1, 2 or 4). This programmable
factor is configured using the CKMODE bit fields in the ADCx_CCR register.
*/

/*

1. select the ADC clock using the function RCC_ADCCLKConfig()
2. Enable the ADC interface clock using RCC_AHBPeriphClockCmd();
3. ADC pins configuration
 Enable the clock for the ADC GPIOs using the following function:
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOx, ENABLE);
 Configure these ADC pins in analog mode using GPIO_Init();
4. Configure the ADC conversion resolution, data alignment, external trigger and edge,
sequencer lenght and Enable/Disable the continuous mode using the ADC_Init()
function.
5. Activate the ADC peripheral using ADC_Cmd() function.

*/

void adcInit()
{
    LL_ADC_Disable(ADC1);
    LL_ADC_InitTypeDef adcInit = { .Resolution = LL_ADC_RESOLUTION_12B,
                                   .DataAlignment = LL_ADC_DATA_ALIGN_RIGHT,
                                   .LowPowerMode = LL_ADC_LP_MODE_NONE };

    if (!LL_ADC_Init(ADC1, &adcInit)) {
        ledWindMillToggleCycle();
    } else {
        led2ToggleCycle();
    }

    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_ADC12);
    // LL_ADC_SetCommonClock(__LL_ADC_COMMON_INSTANCE(ADC1), LL_ADC_CLOCK_ASYNC_DIV1);
    LL_ADC_SetCommonClock(__LL_ADC_COMMON_INSTANCE(ADC1), LL_ADC_CLOCK_SYNC_PCLK_DIV4);
    LL_ADC_SetCommonPathInternalCh(__LL_ADC_COMMON_INSTANCE(ADC1), LL_ADC_PATH_INTERNAL_TEMPSENSOR);
    LL_ADC_REG_SetSequencerLength(ADC1, LL_ADC_REG_SEQ_SCAN_DISABLE);
    LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_TEMPSENSOR);
    LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_TEMPSENSOR, LL_ADC_SAMPLINGTIME_19CYCLES_5);

    delay(1000000);
    LL_ADC_REG_SetContinuousMode(ADC1, LL_ADC_REG_CONV_CONTINUOUS);

    LL_ADC_Enable(ADC1);
    delay(100000);

    if (LL_ADC_IsEnabled(ADC1)) {
        ledWindMillToggleCycle();
    } else {
        led1ToggleCycle();
    }
}

void startConversion()
{
    if (LL_ADC_IsEnabled(ADC1) == 1) {
        LL_ADC_REG_StartConversion(ADC1);
    } else {
        led1ToggleCycle();
        led2ToggleCycle();
        led1ToggleCycle();
    }

    while (LL_ADC_IsActiveFlag_EOC(ADC1)) {
        led2ToggleCycle();
        led3ToggleCycle();
    }
}

void printTemperature()
{
    uint16_t result = LL_ADC_REG_ReadConversionData12(ADC1);
    char adc[4] = {};
    sprintf(&adc, "%d", result);
    displayPuts(0, 3, adc, 1);
}