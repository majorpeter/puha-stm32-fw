/*
 * SystemNode.cpp
 *
 *  Created on: 2018. jan. 7.
 *      Author: peti
 */

#include "SystemNode.h"
#include <stm32f10x.h>

MK_PROP_METHOD(SystemNode, reset, "Restart device");

PROP_ARRAY(props) = {
        PROP_ADDRESS(SystemNode, reset)
};

SystemNode::SystemNode(): Node("SYS") {
    NODE_SET_PROPS(props)
}

ProtocolResult_t SystemNode::invokereset(const char*) {
    NVIC_SystemReset();
    return ProtocolResult_Ok;
}
