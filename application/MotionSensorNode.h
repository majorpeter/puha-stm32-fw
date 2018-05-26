/*
 * MotionSensorNode.h
 *
 *  Created on: 2018. máj. 26.
 *      Author: peti
 */

#ifndef APPLICATION_MOTIONSENSORNODE_H_
#define APPLICATION_MOTIONSENSORNODE_H_

#include "mprotocol-nodes/Node.h"
#include "MotionSensor.h"

class MotionSensorNode: public Node, private MotionSensor::Listener {
public:
    DECLARE_PROP_UINT32_RO(PulseCount);
    DECLARE_PROP_INT32_RO(LastPulseTime);
    DECLARE_PROP_FLOAT32_RO(NoPulseSince);

    MotionSensorNode(MotionSensor* sensor);
    virtual void onPulseDetected(uint32_t index);
private:
    MotionSensor* sensor;
};

#endif /* APPLICATION_MOTIONSENSORNODE_H_ */
