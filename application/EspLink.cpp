/*
 * EspLink.cpp
 *
 *  Created on: 2017. okt. 25.
 *      Author: peti
 */

#include "EspLink.h"

EspLink::EspLink(GPIO_TypeDef * const resetGpioPort, uint16_t resetGpioPin,
        GPIO_TypeDef * const chPdGpioPort, uint16_t chPdGpioPin): UsartSerialInterface(115200) {
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Pin = chPdGpioPin;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(chPdGpioPort, &GPIO_InitStruct);
    GPIO_Init(resetGpioPort, &GPIO_InitStruct);
}
