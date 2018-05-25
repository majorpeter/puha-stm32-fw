/*
 * LightSensor.cpp
 *
 *  Created on: 2018. máj. 23.
 *      Author: peti
 */

#include "LightSensor.h"
#include <stm32f10x_adc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include <string.h>

LightSensor::LightSensor(uint8_t measurementNumber) {
    this->measurementNumber = measurementNumber;
    this->measurementIndex = 0;
    this->measurements = new uint16_t[measurementNumber];
    memset(this->measurements, 0x00, measurementNumber * sizeof(uint16_t));

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // SystemCoreClock = 72 MHz
    // ADCCLK max 14 MHz (see RM Clock Tree) 72/6=12MHz
    RCC_ADCCLKConfig (RCC_PCLK2_Div6);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    ADC_InitTypeDef ADC_InitStruct;
    ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStruct.ADC_ScanConvMode = DISABLE;
    ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStruct.ADC_NbrOfChannel = 1;

    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_239Cycles5);
    ADC_Init(ADC1, &ADC_InitStruct);

    ADC_Cmd(ADC1, ENABLE);

    //  ADC recommended at each power-up
    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1));
}

void LightSensor::handler() {
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);

    measurements[measurementIndex] = ADC_GetConversionValue(ADC1);
    measurementIndex++;
    if (measurementIndex == measurementNumber) {
        measurementIndex = 0;
    }
}

uint16_t LightSensor::getAverageValue() {
    uint16_t sum = 0;
    for (uint8_t i = 0; i < measurementNumber; i++) {
        sum += measurements[i];
    }
    return sum / measurementNumber;
}

float LightSensor::getAverageValueLux() {
    return getValueLux(getAverageValue());
}

float LightSensor::getValueLux(uint16_t measurement) {
    /// reference voltage connected to VDDA pin
    static const float vRef = 3.3f;
    /// it is a 12-bit ADC
    static const uint16_t adcFullScale = 4096;
    /// 1 kOhm
    static const float emitterResistorValue_kOhm = 1.f;
    /// 20 uA -> 20 lx, 100 uA -> 100 lx
    static const float kps_lux_per_mA = 1000.f;

    float measuredVoltage = measurement * vRef / adcFullScale;
    /// R = U/I -> I = U/R
    float measuredCurrent_mA = measuredVoltage / emitterResistorValue_kOhm;

    return measuredCurrent_mA * kps_lux_per_mA;
}
