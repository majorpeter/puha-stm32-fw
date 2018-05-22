/*
 * Htu21D.cpp
 *
 *  Created on: 2018. máj. 18.
 *      Author: peti
 */

#include "Htu21D.h"
#include <iface-i2c/I2cInterface.h>
#include "os/System.h"
#include "htu21d_defs.h"
#include <stddef.h>

using namespace Htu21DRegs;

Htu21D::Htu21D(I2cInterface* i2c): i2c(i2c) {
    state = State_Initial;
    temperature = 0.f;
    humidity = 0.f;
    measurementStartedAt = 0;
    listener = NULL;
}

void Htu21D::setListener(Listener* listener) {
    this->listener = listener;
}

float Htu21D::getTemperature() {
    return temperature;
}

float Htu21D::getHumidity() {
    return humidity;
}

void Htu21D::handler() {
    switch (state) {
    case State_Initial:
        state = State_StartTemperature;
        /* no break */
    case State_StartTemperature: {
        uint8_t command = CommandTriggerTemperatureMeasurement_HoldMaster;
        int8_t result = i2c->write(SlaveAddress8b, &command, 1);
        if (result == 0) {
            state = State_WaitTemperatureMeasurement;
            measurementStartedAt = Os::time_ms();
        }
        break;
    }
    case State_WaitTemperatureMeasurement: {
        int32_t delta = Os::time_ms() - measurementStartedAt;
        if (delta > TemperatureMeasurementMaxTimeMs) {
            state = State_ReadTemperatureMeasurement;
        } else {
            break;
        }
    }
    /* no break */
    case State_ReadTemperatureMeasurement: {
        uint8_t measurementBytes[2];
        int8_t result = i2c->read(SlaveAddress8b, measurementBytes, 2);
        if (result == 0) {
            uint16_t measurement = (measurementBytes[0] << 8) | measurementBytes[1];
            temperature = -46.85f + 175.72f * measurement / 65536.f;
            if (listener != NULL) {
                listener->onTemperatureChanged(temperature);
            }

            // go to next measurement
            state = State_StartHumidity;
        } else {
            // retry
            state = State_StartTemperature;
        }
        break;
    }
    case State_StartHumidity: {
        uint8_t command = CommandTriggerHumidityMeasurement_HoldMaster;
        int8_t result = i2c->write(SlaveAddress8b, &command, 1);
        if (result == 0) {
            state = State_WaitHumidityMeasurement;
            measurementStartedAt = Os::time_ms();
        }
        break;
    }
    case State_WaitHumidityMeasurement: {
        int32_t delta = Os::time_ms() - measurementStartedAt;
        if (delta > HumidityMeasurementMaxTimeMs) {
            state = State_ReadHumidityMeasurement;
        } else {
            break;
        }
    }
    /* no break */
    case State_ReadHumidityMeasurement: {
        uint8_t measurementBytes[2];
        int8_t result = i2c->read(SlaveAddress8b, measurementBytes, 2);
        if (result == 0) {
            uint16_t measurement = (measurementBytes[0] << 8) | (measurementBytes[1] & ~3);
            humidity = -6.f + 125.f * measurement / 65536.f;
            if (listener != NULL) {
                listener->onHumidityChanged(humidity);
            }

            // done
            state = State_Initial;
        } else {
            // retry
            state = State_StartHumidity;
        }
        break;
    }
    }
}
