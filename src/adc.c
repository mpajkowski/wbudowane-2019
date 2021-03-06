#include "adc.h"

short ADC_AVG_VALUE = -1;

static inline void adcCalibrate()
{
    LL_ADC_EnableInternalRegulator(ADC1);
    delay(LL_ADC_DELAY_INTERNAL_REGUL_STAB_US);
    LL_ADC_StartCalibration(ADC1, LL_ADC_DIFFERENTIAL_ENDED);
    while (LL_ADC_IsCalibrationOnGoing(ADC1))
        ;
}

void adcInit()
{
    LL_ADC_Disable(ADC1);
    LL_ADC_InitTypeDef adcInit = { .Resolution = LL_ADC_RESOLUTION_12B,
                                   .DataAlignment = LL_ADC_DATA_ALIGN_RIGHT,
                                   .LowPowerMode = LL_ADC_LP_MODE_NONE };

    if (!LL_ADC_Init(ADC1, &adcInit)) {
        //    ERROR HANDLING
    }

    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_ADC12);

    LL_ADC_SetCommonClock(__LL_ADC_COMMON_INSTANCE(ADC1), LL_ADC_CLOCK_SYNC_PCLK_DIV2);

    LL_ADC_SetCommonPathInternalCh(__LL_ADC_COMMON_INSTANCE(ADC1), LL_ADC_PATH_INTERNAL_NONE);

    LL_ADC_REG_SetSequencerLength(ADC1, LL_ADC_REG_SEQ_SCAN_DISABLE);
    LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_8);
    
    LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_8, LL_ADC_SAMPLINGTIME_181CYCLES_5);
    LL_ADC_REG_SetTriggerSource(ADC1, LL_ADC_REG_TRIG_SOFTWARE);
    LL_ADC_REG_SetContinuousMode(ADC1, LL_ADC_REG_CONV_CONTINUOUS);
    LL_ADC_REG_SetDMATransfer(ADC1, LL_ADC_REG_DMA_TRANSFER_NONE);
    LL_ADC_REG_SetOverrun(ADC1, LL_ADC_REG_OVR_DATA_OVERWRITTEN);

    adcCalibrate();

    LL_ADC_Enable(ADC1);
    while (!LL_ADC_IsActiveFlag_ADRDY(ADC1))
        ;

    if (!LL_ADC_IsEnabled(ADC1)) {
        //    ERROR HANDLING
    }

    LL_ADC_EnableIT_EOS(ADC1);
    NVIC_EnableIRQ(ADC1_IRQn);
}

void ADC1_IRQHandler()
{
    static unsigned short counter;
    static unsigned long acumulator;

    if (counter == SAMPLES_NUMBER) {
        ADC_AVG_VALUE = (float)acumulator / (float)SAMPLES_NUMBER;
        counter = 0;
        acumulator = 0;
    } else {
        acumulator += LL_ADC_REG_ReadConversionData12(ADC1);
        ++counter;
    }

    LL_ADC_ClearFlag_EOS(ADC1);
}

void startConversion()
{
    if (LL_ADC_IsEnabled(ADC1) == 1) {
        LL_ADC_REG_StartConversion(ADC1);
    } else {
        //    ERROR HANDLING
    }
}

float temperatureInterpolation(float resistance, int interval)
{
    static short tempSpread;

    if (interval == TAB_SIZE - 1) {
        return 150.0f;
    } else if (interval == 0) {
        return -55.0f;
    } else {
        tempSpread = TEMP_SENSOR_TAB[interval + 1][0] - TEMP_SENSOR_TAB[interval][0];
    }
    float rest = resistance - TEMP_SENSOR_TAB[interval][2];
    float result = TEMP_SENSOR_TAB[interval + 1][2] - TEMP_SENSOR_TAB[interval][2];
    float ratio = rest / result;
    return TEMP_SENSOR_TAB[interval][0] + (float)tempSpread * ratio;
}

float resistanceToCelcius(float resistance)
{
    // Find resistance interval
    int interval = 0;
    for (; interval < TAB_SIZE; interval++)
        if (resistance < TEMP_SENSOR_TAB[interval][2])
            break;
    return temperatureInterpolation(resistance, interval - 1);
}

static inline void printResistance(char* buffer, unsigned int resistance, uint8_t line)
{
    snprintf(buffer, 11, "R: %u", resistance);
    displayPuts(0, line, buffer, 0);
}

static inline void printVolt(char* buffer, float adcVoltage, uint8_t line)
{
    static int adcVoltageFields[2];
    splitFloat(adcVoltage, adcVoltageFields, 2);
    snprintf(buffer, 11, "Volt: %u.%u", adcVoltageFields[0], adcVoltageFields[1]);
    displayPuts(0, line, buffer, 0);
}

static inline void printTemp(char* buffer, float temp, uint8_t line)
{
    static int tempFields[2];
    splitFloat(temp, tempFields, 1);
    snprintf(buffer, 13, "Temp: %u.%1uC", tempFields[0], tempFields[1]);
    displayPuts(0, line, buffer, 0);
}

static inline void printAdc(char* buffer, unsigned short adcValue, uint8_t line)
{
    if (adcValue == -1) {
        snprintf(buffer, 13, "ADC: NOT RDY");
    } else {
        snprintf(buffer, 11, "ADC: %4u", adcValue);
    }
    displayPuts(0, line, buffer, 0);
}

static inline void printPercentage(char* buffer, unsigned int percent, uint8_t line)
{
    snprintf(buffer, 11, "Perc: %u%%", (unsigned int)percent);
    displayPuts(0, 5, buffer, 0);
}

void printADC()
{
    static char buffer[15] = {};

    if (ADC_AVG_VALUE == -1) {
        snprintf(buffer, 15, "ADC: NOT READY");
        displayPuts(0, 3, buffer, 0);
    } else {
        unsigned int termistorResistance = CALCULATE_TERMISTOR_RESISTANCE(ADC_AVG_VALUE);
        printResistance(buffer, termistorResistance, 2);
        printVolt(buffer, CALCULATE_ADC_VOLTAGE(ADC_AVG_VALUE), 3);
        printAdc(buffer, ADC_AVG_VALUE, 4);
        printTemp(buffer, resistanceToCelcius(termistorResistance), 5);
    }
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