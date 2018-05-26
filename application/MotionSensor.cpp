/*
 * MotionSensor.cpp
 *
 *  Created on: 2018. máj. 26.
 *      Author: peti
 */

#include "MotionSensor.h"
#include "os/System.h"

#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_exti.h>
#include <misc.h>
#include <stddef.h>

static volatile uint32_t pulseCount = 0;

extern "C" void EXTI1_IRQHandler() {
    if (EXTI_GetITStatus(EXTI_Line1) != RESET) {
        pulseCount++;
        EXTI_ClearITPendingBit(EXTI_Line1);
    }
}

MotionSensor::MotionSensor() {
    pulseCount = 0;
    lastPulseTime = 0;
    listener = NULL;

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    EXTI_InitTypeDef EXTI_InitStruct;
    EXTI_InitStruct.EXTI_Line = EXTI_Line1;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStruct);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);

    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}

void MotionSensor::setListener(Listener* listener) {
    this->listener = listener;
}

void MotionSensor::handler() {
    if (pulseCount != ::pulseCount) {
        pulseCount = ::pulseCount;
        lastPulseTime = Os::time_ms();

        if (listener != NULL) {
            listener->onPulseDetected(pulseCount);
        }
    }
}

int32_t MotionSensor::getLastPulseTime() const {
    return lastPulseTime;
}

uint32_t MotionSensor::getPulseCount() const {
    return pulseCount;
}
