/*
 * LightSensor.h
 *
 *  Created on: 2018. máj. 23.
 *      Author: peti
 */

#ifndef APPLICATION_LIGHTSENSOR_H_
#define APPLICATION_LIGHTSENSOR_H_

/**
 * This class measures the ambient light using a Knightbright KPS-3227SP1C
 * sensor and the 1 kOhm resistor connected to the ADC.
 */
class LightSensor {
public:
    LightSensor();
    ~LightSensor() {}
};

#endif /* APPLICATION_LIGHTSENSOR_H_ */
