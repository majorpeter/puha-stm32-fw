/*
 * LightSensorNode.cpp
 *
 *  Created on: 2018. máj. 23.
 *      Author: peti
 */

#include "LightSensorNode.h"

MK_PROP_FLOAT32_RO(LightSensorNode, Illuminance, "Illuminance measurement in Lux");
MK_PROP_FLOAT32_RO(LightSensorNode, Measurement, "Average of raw ADC measurements");

PROP_ARRAY(props) = {
        PROP_ADDRESS(LightSensorNode, Illuminance),
        PROP_ADDRESS(LightSensorNode, Measurement),
};

LightSensorNode::LightSensorNode(LightSensor* sensor) :
        Node("LIGHT", "Light sensor measurement"), sensor(sensor) {
    NODE_SET_PROPS(props);

    sensor->setListener(this);
}

ProtocolResult_t LightSensorNode::getIlluminance(float* dest) const {
    *dest = sensor->getAverageValueLux();
    return ProtocolResult_Ok;
}

ProtocolResult_t LightSensorNode::getMeasurement(float* dest) const {
    *dest = sensor->getAverageValue();
    return ProtocolResult_Ok;
}

void LightSensorNode::onValueChanged(LightSensor*) {
    invalidateProperty(&prop_Illuminance);
    invalidateProperty(&prop_Measurement);
}
