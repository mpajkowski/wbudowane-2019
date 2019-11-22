// #include "temperature.h"
// #include "led.h"
// #include <stm32f3xx_ll_rcc.h>
// #include <stm32f3xx_ll_adc.h>
// #include <stm32f3xx_ll_bus.h>
// #include <stm32f3xx_ll_gpio.h>

// #define TEMP_SENSOR_AVG_SLOPE_MV_PER_CELSIUS                        2.5f
// #define TEMP_SENSOR_VOLTAGE_MV_AT_25                                3.0f
// #define ADC_REFERENCE_VOLTAGE_MV                                    3.3f
// #define ADC_MAX_OUTPUT_VALUE                                        4095.0f


// void ADC_calibration(){
// //    LL_ADC_ResetCalibration(ADC1);

//    ADC1->CR &= ~ADC_CR_ADEN;
//    ADC1->CR |= ADC_CR_ADCAL;
//    while((ADC1->CR & ADC_CR_ADCAL) != 0){}
// }

// void initTempearture(){

//    ADC_calibration();
//    ENABLE_ADC1_CLOCK;

//    LL_ADC_SetCommonClock(__LL_ADC_COMMON_INSTANCE(ADC1), LL_ADC_CLOCK_SYNC_PCLK_DIV2);
//    LL_ADC_SetCommonPathInternalCh(__LL_ADC_COMMON_INSTANCE(ADC1), LL_ADC_PATH_INTERNAL_TEMPSENSOR);

//    LL_ADC_Enable(ADC1);

//     if(LL_ADC_IsEnabled(ADC1) == 0){
//         led2ToggleCycle();
//     }
//     else{
//         led1ToggleCycle();
//     }

//     // LL_ADC_CHANNEL_TEMPSENSOR
// }

// int readADC1()
// {
//   //LL_ADC_REG_InitTypeDef


//   LL_ADC_REG_StartConversion(ADC1);
//   while(LL_ADC_REG_IsConversionOngoing(ADC1) != 0){
//     LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_TEMPSENSOR, LL_ADC_SAMPLINGTIME_2CYCLES_5);
//     led2ToggleCycle();
//      led2ToggleCycle();
//   }
//     led1ToggleCycle();
//     int value = LL_ADC_REG_ReadConversionData10(ADC1);
    
//   LL_ADC_REG_StopConversion(ADC1);
    

// // ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_1Cycles5);
//   // Start the conversion
// //   ADC_SoftwareStartConvCmd(ADC1, ENABLE);
//   // Wait until conversion completion
// //   while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
//   // Get the conversion value
// //   return ADC_GetConversionValue(ADC1);

//     int32_t sensorValue = value;

//     sensorValue = sensorValue * ADC_REFERENCE_VOLTAGE_MV / ADC_MAX_OUTPUT_VALUE;
//     int32_t temperature = (int32_t)((sensorValue - TEMP_SENSOR_VOLTAGE_MV_AT_25) / TEMP_SENSOR_AVG_SLOPE_MV_PER_CELSIUS + 25);


//     return temperature;
// }