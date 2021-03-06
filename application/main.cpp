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
#include "LightSensor.h"
#include "LightSensorNode.h"
#include "MotionSensor.h"
#include "MotionSensorNode.h"
#include "hardware_config.h"

#include <string.h>

int main() {
    Hardware::RCC_Init();
    Hardware::LiveLedInit();
    Hardware::GPIO_Remap();
    Hardware::IRQ_Init();

    RootNode::getInstance()->addChild(new SystemNode());

#ifdef HWCONFIG_LEDSTRIP_PRESENT
    LedStripController ledStrip(Hardware::LedStripDataOutPort, Hardware::LedStripDataOutPin, 180, 0, false);
    ledStrip.init();
    ledStrip.writeLeds(NULL, 0);
    RootNode::getInstance()->addChild(new LedStripControllerNode(&ledStrip));
#endif /* HWCONFIG_LEDSTRIP_PRESENT */

#ifdef HWCONFIG_HTU_PRESENT
    Stm32F1I2c::InitStruct initStruct = {
            .i2cPeriph = Hardware::Htu21DI2c,
            .sdaSclPort = Hardware::Htu21DSdaSclPort,
            .sdaPin = Hardware::Htu21DSdaPin,
            .sclPin = Hardware::Htu21DSclPin,
            .clockSpeedHz = 100000
    };
    Stm32F1I2c* htu21dI2c = new Stm32F1I2c(&initStruct);
    Htu21D* htu21d = new Htu21D(htu21dI2c);
    RootNode::getInstance()->addChild(new Htu21DNode(htu21d));
#endif /* HWCONFIG_HTU_PRESENT */

#ifdef HWCONFIG_LIGHTSENSOR_PRESENT
    LightSensor* lightSensor = new LightSensor(4096);
    LightSensorNode* lightSensorNode = new LightSensorNode(lightSensor);
    RootNode::getInstance()->addChild(lightSensorNode);
#endif /* HWCONFIG_LIGHTSENSOR_PRESENT */

#ifdef HWCONFIG_MOTIONSENSOR_PRESENT
    MotionSensor* motionSensor = new MotionSensor();
    RootNode::getInstance()->addChild(new MotionSensorNode(motionSensor));
#endif /* HWCONFIG_MOTIONSENSOR_PRESENT */

#ifdef HWCONFIG_USART_PRESENT
    UsartSerialInterface* serialInterface = new UsartSerialInterface(460800);
    ProtocolParser* protocol = new ProtocolParser(serialInterface);
    serialInterface->listen();
#endif /* HWCONFIG_USART_PRESENT */

    Os::start();
    while (1) {
        Hardware::LiveLedToggle();
#ifdef HWCONFIG_USART_PRESENT
        protocol->handler();
#endif

#ifdef HWCONFIG_HTU_PRESENT
        htu21d->handler();
#endif

#ifdef HWCONFIG_LIGHTSENSOR_PRESENT
        lightSensor->handler();
#endif

#ifdef HWCONFIG_MOTIONSENSOR_PRESENT
        motionSensor->handler();
#endif
    }

    return 0;
}
