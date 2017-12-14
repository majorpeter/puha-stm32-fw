/*
 * EspLink.h
 *
 *  Created on: 2017. okt. 25.
 *      Author: peti
 */

#ifndef ESPLINK_H_
#define ESPLINK_H_

#include <mprotocol-iface-stm32-usart/UsartSerialInterface.h>
#include <stm32f10x.h>

/**
 * This class is a wrapper aruound mprotocol-iface-stm32-usart
 *
 * It is useful when using an ESP8266 (or similar) module with the esp-link firmware (wifi-uart bridge).
 * This class simply handles its GPIO's.
 */
class EspLink: public UsartSerialInterface {
public:
    EspLink(GPIO_TypeDef * const resetGpioPort, uint16_t resetGpioPin,
            GPIO_TypeDef * const chPdGpioPort, uint16_t chPdGpioPin);
    virtual ~EspLink() {}
};

#endif /* ESPLINK_H_ */
