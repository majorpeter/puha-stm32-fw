/*
 * LightSensorNode.cpp
 *
 *  Created on: 2018. máj. 23.
 *      Author: peti
 */

#include "LightSensorNode.h"
#include "LightSensor.h"

MK_PROP_FLOAT32_RO(LightSensorNode, Illuminance, "Illuminance measurement in Lux");

PROP_ARRAY(props) = {
        PROP_ADDRESS(LightSensorNode, Illuminance)
};

LightSensorNode::LightSensorNode(LightSensor* sensor) :
        Node("LIGHT", "Light sensor measurement"), sensor(sensor) {
    NODE_SET_PROPS(props);
}

ProtocolResult_t LightSensorNode::getIlluminance(float* dest) const {
    *dest = sensor->getValueLux();
    return ProtocolResult_Ok;
}

void LightSensorNode::handler() {
    invalidateProperty(&prop_Illuminance);
}
