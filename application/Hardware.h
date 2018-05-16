/*
 * Hardware.h
 *
 *  Created on: 2017. aug. 5.
 *      Author: peti
 */

#ifndef HARDWARE_H_
#define HARDWARE_H_

#include <stm32f10x.h>

class Qep;
class FunctionButton;

namespace Hardware {

static GPIO_TypeDef * const LedStripDataOutPort = GPIOB;
static const uint16_t LedStripDataOutPin =  GPIO_Pin_12;

void RCC_Init();
void GPIO_Remap();
void SysTickInit();
void RTC_Init();
void IRQ_Init();

Qep* createRotaryEncoder();
FunctionButton* createFunctionButton();

}

#endif /* HARDWARE_H_ */
