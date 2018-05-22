/*
 * Htu21D.cpp
 *
 *  Created on: 2018. máj. 18.
 *      Author: peti
 */

#include "Htu21D.h"
#include <iface-i2c/I2cInterface.h>
#include "htu21d_defs.h"

using namespace Htu21DRegs;

Htu21D::Htu21D(I2cInterface* i2c): i2c(i2c) {
}

int8_t Htu21D::getTemperature(float* dest) {
    uint8_t command = CommandTriggerTemperatureMeasurement_HoldMaster;
    int8_t result = i2c->write(SlaveAddress8b, &command, 1);
    if (result != 0) {
        return result;
    }

    uint8_t measurementBytes[2];
    result = i2c->read(SlaveAddress8b, measurementBytes, 2);
    if (result != 0) {
        return result;
    }

    uint16_t measurement = (measurementBytes[0] << 8) | measurementBytes[1];
    *dest = -46.85f + 175.72f * measurement / 65536;
    return 0;
}
