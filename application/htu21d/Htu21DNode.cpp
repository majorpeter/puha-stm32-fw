/*
 * Htu21DNode.cpp
 *
 *  Created on: 2018. máj. 22.
 *      Author: peti
 */

#include "Htu21DNode.h"
#include "Htu21D.h"

MK_PROP_FLOAT32_RO(Htu21DNode, Temperature, "Temparature in °C");

PROP_ARRAY(props) = {
        PROP_ADDRESS(Htu21DNode, Temperature)
};

Htu21DNode::Htu21DNode(Htu21D* htu21d): Node("HTU", "HTU21D sensor measurements"), htu21d(htu21d) {
    NODE_SET_PROPS(props);
}

ProtocolResult_t Htu21DNode::getTemperature(float* dest) const {
    *dest = htu21d->getTemperature();
    return ProtocolResult_Ok;
}
