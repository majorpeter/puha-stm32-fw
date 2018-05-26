/*
 * MotionSensorNode.cpp
 *
 *  Created on: 2018. máj. 26.
 *      Author: peti
 */

#include "MotionSensorNode.h"
#include "os/System.h"

MK_PROP_UINT32_RO(MotionSensorNode, PulseCount, "Number of detected pulses since startup");
MK_PROP_INT32_RO(MotionSensorNode, LastPulseTime, "Timestamp of last detected pulse in ms");
MK_PROP_FLOAT32_RO(MotionSensorNode, NoPulseSince, "Seconds since the last pulse");

PROP_ARRAY(props) = {
        PROP_ADDRESS(MotionSensorNode, PulseCount),
        PROP_ADDRESS(MotionSensorNode, LastPulseTime),
        PROP_ADDRESS(MotionSensorNode, NoPulseSince),
};

MotionSensorNode::MotionSensorNode(MotionSensor* sensor) :
        Node("MOTION", "HC-SR501 motion sensor"), sensor(sensor) {
    NODE_SET_PROPS(props);
    sensor->setListener(this);
}

void MotionSensorNode::onPulseDetected(uint32_t) {
    invalidateProperty(&prop_PulseCount);
    invalidateProperty(&prop_LastPulseTime);
    invalidateProperty(&prop_NoPulseSince);
}

ProtocolResult_t MotionSensorNode::getPulseCount(uint32_t* dest) const {
    *dest = sensor->getPulseCount();
    return ProtocolResult_Ok;
}

ProtocolResult_t MotionSensorNode::getLastPulseTime(int32_t* dest) const {
    *dest = sensor->getLastPulseTime();
    return ProtocolResult_Ok;
}

ProtocolResult_t MotionSensorNode::getNoPulseSince(float* dest) const {
    int32_t duration = Os::time_ms() - sensor->getLastPulseTime();
    *dest = duration / 1000.f;
    return ProtocolResult_Ok;
}
