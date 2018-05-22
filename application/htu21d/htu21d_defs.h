/*
 * htu21d_regs.h
 *
 *  Created on: 2018. máj. 18.
 *      Author: peti
 */

#ifndef MODULES_HTU21D_HTU21D_DEFS_H_
#define MODULES_HTU21D_HTU21D_DEFS_H_

#include <stdint.h>

namespace Htu21DRegs {

static const uint8_t SlaveAddress8b = 0x80;

static const uint8_t CommandTriggerTemperatureMeasurement_HoldMaster = 0xe3;
static const uint8_t CommandTriggerHumidityMeasurement_HoldMaster = 0xe5;
static const uint8_t CommandTriggerTemperatureMeasurement_NoHoldMaster = 0xf3;
static const uint8_t CommandTriggerHumidityMeasurement_NoHoldMaster = 0xf5;
static const uint8_t CommandWriteUserReg = 0xe6;
static const uint8_t CommandReadUserReg = 0xe7;
static const uint8_t CommandSoftReset = 0xfe;

static const uint8_t TemperatureMeasurementMaxTimeMs = 100;

} /* namespace Htu21DRegs */

#endif /* MODULES_HTU21D_HTU21D_DEFS_H_ */
