#include "Hardware.h"
#include "diag/Trace.h"

#include "EspLink.h"
#include <ws2812-stm32/LedStripController.h>
#include <mprotocol-server/ProtocolParser.h>
#include <mprotocol-nodes/RootNode.h>

#include <string.h>

int main() {
    Hardware::RCC_Init();
    Hardware::GPIO_Remap();
    Hardware::SysTickInit();
    Hardware::IRQ_Init();

    /*Canvas* canvas = new HardwareCanvas(Hardware::LedStripDataOutPort, Hardware::LedStripDataOutPin, 180, 0, false);
    canvas->init();
    for (uint8_t i = 0; i < 10; i++) {
        canvas->set(i, Color::red * ((10 - i) / 10.f));
    }
    canvas->draw();*/

    EspLink* serialInterface = new EspLink(Hardware::EspResetPort,
            Hardware::EspResetPin, Hardware::EspChPdPort, Hardware::EspChPdPin);
    ProtocolParser* protocol = new ProtocolParser(serialInterface);
    serialInterface->listen();

    while (1) {
        protocol->handler();
    }

    return 0;
}
