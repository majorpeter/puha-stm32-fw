/*
 * SystemNode.cpp
 *
 *  Created on: 2018. jan. 7.
 *      Author: peti
 */

#include "SystemNode.h"
#include "os/System.h"
#include <stm32f10x.h>

MK_PROP_METHOD(SystemNode, reset, "Restart device");
MK_PROP_INT32_RO(SystemNode, TimeMs, "Time since boot in ms");

PROP_ARRAY(props) = {
        PROP_ADDRESS(SystemNode, reset),
        PROP_ADDRESS(SystemNode, TimeMs)
};

SystemNode::SystemNode(): Node("SYS") {
    NODE_SET_PROPS(props)
}

ProtocolResult_t SystemNode::invokereset(const char*) {
    NVIC_SystemReset();
    return ProtocolResult_Ok;
}

ProtocolResult_t SystemNode::getTimeMs(int32_t* dest) const {
    *dest = Os::time_ms();
    return ProtocolResult_Ok;
}
