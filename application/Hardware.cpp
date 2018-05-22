/*
 * Hardware.cpp
 *
 *  Created on: 2017. aug. 5.
 *      Author: peti
 */

#include "Hardware.h"

#include <stm32f10x_gpio.h>

namespace Hardware {

void RCC_Init() {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP | RCC_APB1Periph_PWR, ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
}

void GPIO_Remap() {
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
}

/**
 * Configure SysTick interrupt in every 1ms
 */
void SysTickInit() {
    SysTick_Config(SystemCoreClock / 1000);
}

void IRQ_Init() {
    // 4 bits for pre-emption priority: NVIC_IRQChannelPreemptionPriority = 0..15
    // 0 bits for subpriority:          NVIC_IRQChannelSubPriority        = 0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

    NVIC_InitTypeDef    NVIC_InitStructure;

    // DMA1 Channel7
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel7_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // TIM2
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


void LiveLedInit() {
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = LiveLedPin;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_Init(LiveLedPort, &GPIO_InitStruct);

    GPIO_ResetBits(LiveLedPort, LiveLedPin);
}

void LiveLedToggle() {
    GPIO_WriteBit(LiveLedPort, LiveLedPin, (BitAction) !GPIO_ReadInputDataBit(LiveLedPort, LiveLedPin));
}

}
