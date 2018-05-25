/*
 * LightSensorNode.cpp
 *
 *  Created on: 2018. máj. 23.
 *      Author: peti
 */

#include "LightSensorNode.h"
#include "LightSensor.h"

MK_PROP_FLOAT32_RO(LightSensorNode, Illuminance, "Illuminance measurement in Lux");
MK_PROP_UINT32_RO(LightSensorNode, Measurement, "Raw ADC measurement");

PROP_ARRAY(props) = {
        PROP_ADDRESS(LightSensorNode, Illuminance),
        PROP_ADDRESS(LightSensorNode, Measurement),
};

LightSensorNode::LightSensorNode(LightSensor* sensor) :
        Node("LIGHT", "Light sensor measurement"), sensor(sensor) {
    NODE_SET_PROPS(props);
}

ProtocolResult_t LightSensorNode::getIlluminance(float* dest) const {
    *dest = sensor->getAverageValueLux();
    return ProtocolResult_Ok;
}

ProtocolResult_t LightSensorNode::getMeasurement(uint32_t* dest) const {
    *dest = sensor->getAverageValue();
    return ProtocolResult_Ok;
}

void LightSensorNode::handler() {
    invalidateProperty(&prop_Illuminance);
}
