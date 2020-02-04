#ifndef _ADC_H
#define _ADC_H

#include "display.h"
#include "led.h"
#include "utils.h"
#include <stdlib.h>
#include <stm32f3xx_ll_adc.h>
#include <stm32f3xx_ll_exti.h>
#include <stm32f3xx_ll_gpio.h>
#include <stm32f3xx_ll_rcc.h>

#define ENABLE_TEMPERATURE_INPUT_GPIO LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA)
#define TEMPERATURE_PORT GPIOC
#define TEMPERATURE_PIN LL_GPIO_PIN_2
#define SUPPLY_VOLTAGE 3.0f
#define ADC_RESOLUTION 4095.0f
#define EXEMPLARY_RESISTOR 1942.0f
#define SAMPLES_NUMBER 500

#define CALCULATE_ADC_VOLTAGE(ADC_VALUE) (SUPPLY_VOLTAGE * ADC_AVG_VALUE) / ADC_RESOLUTION
#define CALCULATE_ADC_PERCENTAGE(ADC_VALUE) (ADC_AVG_VALUE / ADC_RESOLUTION) * 100.0f
#define CALCULATE_TERMISTOR_RESISTANCE(ADC_VALUE)                                                  \
    (unsigned int)(EXEMPLARY_RESISTOR / (ADC_RESOLUTION / (float)ADC_AVG_VALUE - 1.0f))

#define TEMP_SENSOR KTY_81_210

#ifdef TEMP_SENSOR
    #if TEMP_SENSOR == KTY_81_210
    #define TAB_SIZE 24
    /*
        KTY_81_210_TAB
        [0] -> Ambient temperature (°C)
        [1] -> Temperature coefficient (%/K)
        [2] -> AVG Resistance (Ω)
    */
    static const float TEMP_SENSOR_TAB[TAB_SIZE][3] = {
        { -55.0, 0.99, 980.0 },  { -50.0, 0.98, 1030.0 }, { -40.0, 0.96, 1135.0 },
        { -30.0, 0.93, 1247.0 }, { -20.0, 0.91, 1367.0 }, { -10.0, 0.88, 1495.0 },
        { 0.0, 0.85, 1630.0 },   { 10.0, 0.83, 1772.0 },  { 20.0, 0.8, 1922.0 },
        { 25.0, 0.79, 2000.0 },  { 30.0, 0.78, 2080.0 },  { 40.0, 0.75, 2245.0 },
        { 50.0, 0.73, 2417.0 },  { 60.0, 0.71, 2597.0 },  { 70.0, 0.69, 2785.0 },
        { 80.0, 0.67, 2980.0 },  { 90.0, 0.65, 3182.0 },  { 100.0, 0.63, 3392.0 },
        { 110.0, 0.59, 3607.0 }, { 120.0, 0.53, 3817.0 }, { 125.0, 0.49, 3915.0 },
        { 130.0, 0.44, 4008.0 }, { 140.0, 0.33, 4166.0 }, { 150.0, 0.2, 4280.0 }
    };
    #endif
#else
    #error TEMPERATURE SENSOR NOT DEFINIED
#endif

extern short ADC_AVG_VALUE;
void adcInit();
void analogInputInit();
void startConversion();
void printADC();

#endif