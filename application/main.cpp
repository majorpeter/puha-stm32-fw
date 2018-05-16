#include "Hardware.h"
#include "diag/Trace.h"

#include "nodes/SystemNode.h"
#include <ws2812-stm32/LedStripController.h>
#include <ws2812-stm32/Color.h>
#include <ws2812-stm32/node/LedStripControllerNode.h>
#include <mprotocol-server/ProtocolParser.h>
#include <mprotocol-iface-stm32-usart/UsartSerialInterface.h>
#include <mprotocol-nodes/RootNode.h>

#include <string.h>

int main() {
    Hardware::RCC_Init();
    Hardware::GPIO_Remap();
    Hardware::SysTickInit();
    Hardware::IRQ_Init();

    RootNode::getInstance()->addChild(new SystemNode());

    LedStripController ledStrip(Hardware::LedStripDataOutPort, Hardware::LedStripDataOutPin, 180, 0, false);
    ledStrip.init();
    ledStrip.writeLeds(NULL, 0);
    RootNode::getInstance()->addChild(new LedStripControllerNode(&ledStrip));

    UsartSerialInterface* serialInterface = new UsartSerialInterface(460800);
    ProtocolParser* protocol = new ProtocolParser(serialInterface);
    serialInterface->listen();

    while (1) {
        protocol->handler();
    }

    return 0;
}
