#include "Hardware.h"
#include "diag/Trace.h"

#include "EspLink.h"
#include <ws2812-stm32/LedStripController.h>
#include <ws2812-stm32/Color.h>
#include <ws2812-stm32/node/LedStripControllerNode.h>
#include <mprotocol-server/ProtocolParser.h>
#include <mprotocol-nodes/RootNode.h>

#include <string.h>

int main() {
    Hardware::RCC_Init();
    Hardware::GPIO_Remap();
    Hardware::SysTickInit();
    Hardware::IRQ_Init();

    LedStripController ledStrip(Hardware::LedStripDataOutPort, Hardware::LedStripDataOutPin, 180, 0, false);
    ledStrip.init();
    Color colors[180];
    for (uint8_t i = 0; i < 10; i++) {
        colors[i] = Color::red * ((10 - i) / 10.f);
    }
    ledStrip.writeLeds(colors, 180);
    RootNode::getInstance()->addChild(new LedStripControllerNode(&ledStrip));

    EspLink* serialInterface = new EspLink(Hardware::EspResetPort,
            Hardware::EspResetPin, Hardware::EspChPdPort, Hardware::EspChPdPin);
    ProtocolParser* protocol = new ProtocolParser(serialInterface);
    serialInterface->listen();

    while (1) {
        protocol->handler();
    }

    return 0;
}
