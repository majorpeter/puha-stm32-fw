/*
 * LightSensorNode.h
 *
 *  Created on: 2018. máj. 23.
 *      Author: peti
 */

#ifndef APPLICATION_LIGHTSENSORNODE_H_
#define APPLICATION_LIGHTSENSORNODE_H_

#include <mprotocol-nodes/Node.h>
#include "LightSensor.h"

class LightSensorNode: public Node, private LightSensor::Listener {
public:
    DECLARE_PROP_FLOAT32_RO(Illuminance);
    DECLARE_PROP_UINT32_RO(Measurement);

    LightSensorNode(LightSensor* sensor);
private:
    LightSensor* sensor;

    virtual void onValueChanged(LightSensor* sender);
};

#endif /* APPLICATION_LIGHTSENSORNODE_H_ */
