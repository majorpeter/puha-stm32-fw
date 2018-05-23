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

static I2C_TypeDef * const Htu21DI2c = I2C1;
static GPIO_TypeDef * const Htu21DSdaSclPort = GPIOB;
static const uint16_t Htu21DSdaPin = GPIO_Pin_7;
static const uint16_t Htu21DSclPin = GPIO_Pin_6;

void RCC_Init();
void GPIO_Remap();
void RTC_Init();
void IRQ_Init();
void LiveLedInit();
void LiveLedToggle();

}

#endif /* HARDWARE_H_ */
