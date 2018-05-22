/*
 * Hardware.h
 *
 *  Created on: 2017. aug. 5.
 *      Author: peti
 */

#ifndef HARDWARE_H_
#define HARDWARE_H_

#include <stm32f10x.h>

namespace Hardware {

static GPIO_TypeDef * const LedStripDataOutPort = GPIOB;
static const uint16_t LedStripDataOutPin =  GPIO_Pin_12;

static GPIO_TypeDef * const LiveLedPort = GPIOC;
static const uint16_t LiveLedPin =  GPIO_Pin_13;

void RCC_Init();
void GPIO_Remap();
void SysTickInit();
void RTC_Init();
void IRQ_Init();
void LiveLedInit();
void LiveLedToggle();

}

#endif /* HARDWARE_H_ */
