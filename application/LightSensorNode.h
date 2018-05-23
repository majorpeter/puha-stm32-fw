/*
 * LightSensorNode.h
 *
 *  Created on: 2018. máj. 23.
 *      Author: peti
 */

#ifndef APPLICATION_LIGHTSENSORNODE_H_
#define APPLICATION_LIGHTSENSORNODE_H_

#include <mprotocol-nodes/Node.h>

class LightSensor;

class LightSensorNode: public Node {
public:
    DECLARE_PROP_FLOAT32_RO(Illuminance);

    LightSensorNode(LightSensor* sensor);
    void handler();
private:
    LightSensor* sensor;
};

#endif /* APPLICATION_LIGHTSENSORNODE_H_ */
