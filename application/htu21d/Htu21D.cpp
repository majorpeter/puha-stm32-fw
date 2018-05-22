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

using namespace Htu21DRegs;

Htu21D::Htu21D(I2cInterface* i2c): i2c(i2c) {
    state = State_Initial;
    temperature = 0.f;
    measurementStartedAt = 0;
}

float Htu21D::getTemperature() {
    return temperature;
}

void Htu21D::handler() {
    switch (state) {
    case State_Initial:
        state = State_StartTemp;
        /* no break */
    case State_StartTemp: {
        uint8_t command = CommandTriggerTemperatureMeasurement_HoldMaster;
        int8_t result = i2c->write(SlaveAddress8b, &command, 1);
        if (result == 0) {
            state = State_WaitTempMeas;
            measurementStartedAt = Os::time_ms();
        }
        break;
    }
    case State_WaitTempMeas: {
        int32_t delta = Os::time_ms() - measurementStartedAt;
        if (delta > TemperatureMeasurementMaxTimeMs) {
            state = State_ReadTempMeas;
        } else {
            break;
        }
    }
    /* no break */
    case State_ReadTempMeas: {
        uint8_t measurementBytes[2];
        int8_t result = i2c->read(SlaveAddress8b, measurementBytes, 2);
        if (result == 0) {
            uint16_t measurement = (measurementBytes[0] << 8) | measurementBytes[1];
            temperature = -46.85f + 175.72f * measurement / 65536;
            state = State_Initial;
        } else {
            state = State_StartTemp;
        }
        break;
    }
    }
}
