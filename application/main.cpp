#include "Hardware.h"
#include "diag/Trace.h"

#include "nodes/SystemNode.h"
#include <ws2812-stm32/LedStripController.h>
#include <ws2812-stm32/Color.h>
#include <ws2812-stm32/node/LedStripControllerNode.h>
#include <mprotocol-server/ProtocolParser.h>
#include <mprotocol-iface-stm32-usart/UsartSerialInterface.h>
#include <mprotocol-nodes/RootNode.h>
#include <iface-i2c-stm32f1/Stm32F1I2c.h>
#include "os/System.h"
#include "htu21d/Htu21D.h"
#include "htu21d/Htu21DNode.h"

#include <string.h>

int main() {
    Hardware::RCC_Init();
    Hardware::LiveLedInit();
    Hardware::GPIO_Remap();
    Hardware::IRQ_Init();

    RootNode::getInstance()->addChild(new SystemNode());

    LedStripController ledStrip(Hardware::LedStripDataOutPort, Hardware::LedStripDataOutPin, 180, 0, false);
    ledStrip.init();
    ledStrip.writeLeds(NULL, 0);
    RootNode::getInstance()->addChild(new LedStripControllerNode(&ledStrip));

    Stm32F1I2c::InitStruct initStruct = {
            .i2cPeriph = I2C1,
            .sdaSclPort = GPIOB,
            .sdaPin = GPIO_Pin_7,
            .sclPin = GPIO_Pin_6,
            .clockSpeedHz = 100000
    };
    Stm32F1I2c* htu21dI2c = new Stm32F1I2c(&initStruct);
    Htu21D* htu21d = new Htu21D(htu21dI2c);
    RootNode::getInstance()->addChild(new Htu21DNode(htu21d));

    UsartSerialInterface* serialInterface = new UsartSerialInterface(460800);
    ProtocolParser* protocol = new ProtocolParser(serialInterface);
    serialInterface->listen();

    Os::start();
    while (1) {
        Hardware::LiveLedToggle();
        protocol->handler();
        htu21d->handler();
    }

    return 0;
}
