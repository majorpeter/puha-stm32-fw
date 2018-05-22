/*
 * System.cpp
 *
 *  Created on: 2018. máj. 22.
 *      Author: peti
 */

#include "System.h"
#include <stm32f10x.h>

namespace Os {

static int32_t tick = 0;

void start() {
    // Configure SysTick interrupt in every 1ms
    SysTick_Config(SystemCoreClock / 1000);
}

int32_t time_ms() {
    return tick;
}

} /* namespace Os */

extern "C" void SysTick_Handler(void) {
    Os::tick++;
}
