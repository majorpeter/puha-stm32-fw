/*
 * LightSensor.h
 *
 *  Created on: 2018. máj. 23.
 *      Author: peti
 */

#ifndef APPLICATION_LIGHTSENSOR_H_
#define APPLICATION_LIGHTSENSOR_H_

#include <stdint.h>

/**
 * This class measures the ambient light using a Knightbright KPS-3227SP1C
 * sensor and the 1 kOhm resistor connected to the ADC.
 */
class LightSensor {
public:
    class Listener {
    public:
        virtual void onValueChanged(LightSensor* sender) = 0;
        virtual ~Listener() {}
    };

    LightSensor(uint16_t sampleNumber);
    ~LightSensor() {}
    void setListener(Listener* listener);

    void handler();

    float getAverageValue();
    float getAverageValueLux();
    static float getValueLux(uint16_t measurement);
private:
    uint32_t measurementSum;
    float measurementAverage;
    uint16_t measurementIndex;
    const uint16_t measurementNumber;

    Listener* listener;

    void hardwareInit();
};

#endif /* APPLICATION_LIGHTSENSOR_H_ */
