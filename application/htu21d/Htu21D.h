/*
 * Htu21D.h
 *
 *  Created on: 2018. máj. 18.
 *      Author: peti
 */

#ifndef MODULES_HTU21D_HTU21D_H_
#define MODULES_HTU21D_HTU21D_H_

#include <stdint.h>

class I2cInterface;

class Htu21D {
public:
    Htu21D(I2cInterface* i2c);
    ~Htu21D() {}

    float getTemperature();
    float getHumidity();
    void handler();
private:
    I2cInterface* i2c;
    enum {
        State_Initial = 0,
        State_StartTemperature,
        State_WaitTemperatureMeasurement,
        State_ReadTemperatureMeasurement,
        State_StartHumidity,
        State_WaitHumidityMeasurement,
        State_ReadHumidityMeasurement,
    } state;

    float temperature;
    float humidity;

    int32_t measurementStartedAt;
};

#endif /* MODULES_HTU21D_HTU21D_H_ */
