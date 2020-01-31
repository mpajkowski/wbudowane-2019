#include "adc.h"
#include "utils.h"
#include <math.h>

void adcInit()
{
    // LL_ADC_SetCalibrationFactor(ADC1, LL_ADC_CALIBRA)
    // LL_ADC_StartCalibration(ADC1);
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

    LL_ADC_SetCommonClock(__LL_ADC_COMMON_INSTANCE(ADC1), LL_ADC_CLOCK_SYNC_PCLK_DIV2);

    LL_ADC_SetCommonPathInternalCh(__LL_ADC_COMMON_INSTANCE(ADC1), LL_ADC_PATH_INTERNAL_NONE);

    LL_ADC_REG_SetSequencerLength(ADC1, LL_ADC_REG_SEQ_SCAN_DISABLE);

    LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_4);
    LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_4, LL_ADC_SAMPLINGTIME_181CYCLES_5);

    delay(10000000);
    LL_ADC_REG_SetTriggerSource(ADC1, LL_ADC_REG_TRIG_SOFTWARE);
    LL_ADC_REG_SetContinuousMode(ADC1, LL_ADC_REG_CONV_CONTINUOUS);
    LL_ADC_REG_SetDMATransfer(ADC1, LL_ADC_REG_DMA_TRANSFER_NONE);

    LL_ADC_REG_SetOverrun(ADC1, LL_ADC_REG_OVR_DATA_OVERWRITTEN);

    LL_ADC_EnableInternalRegulator(ADC1);
    delay(1000000);

    LL_ADC_StartCalibration(ADC1, LL_ADC_DIFFERENTIAL_ENDED);
    while (LL_ADC_IsCalibrationOnGoing(ADC1)) {
        led3ToggleCycle();
    }

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

void printADC()
{
    const float SupplyVoltage = 3.0f; // [Volts]
    const float ADCResolution = 4095.0f;
    const float re_resistor = 2000.0f;

    

    int16_t result = LL_ADC_REG_ReadConversionData12(ADC1);

    float vsense =
      (SupplyVoltage * result) / ADCResolution; 

    float percent = result / ADCResolution;
    percent *= 100.0f;

    float rx_resistor = re_resistor / (ADCResolution / (float)result - 1.0f);

    unsigned int vsenseInt = (unsigned int)vsense;
    float vsenseFrac = vsense - vsenseInt;
    int vsenseInt2 = trunc(vsenseFrac * 100);

    int resistor = (unsigned int)rx_resistor;

    static char adc[11] = {};
    snprintf(adc, 11, "R: %u", resistor);
    displayPuts(0, 2, adc, 0);
    snprintf(adc, 11, "Volt: %u.%u2", vsenseInt, vsenseInt2);
    displayPuts(0, 3, adc, 0);
    snprintf(adc, 11, "ADC: %u", (unsigned int)result);
    displayPuts(0, 4, adc, 0);
    snprintf(adc, 11, "Perc: %u%%", (unsigned int)percent);
    displayPuts(0, 5, adc, 0);
}

void analogInputInit()
{
    ENABLE_TEMPERATURE_INPUT_GPIO;

    LL_GPIO_InitTypeDef gpio = {
        .Pin = TEMPERATURE_PIN,
        .Mode = LL_GPIO_MODE_ANALOG,
        .Speed = LL_GPIO_SPEED_FREQ_HIGH,
        .Pull = LL_GPIO_PULL_NO,
    };

    LL_GPIO_Init(TEMPERATURE_PORT, &gpio);
}