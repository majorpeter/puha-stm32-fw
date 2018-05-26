/*
 * MotionSensor.h
 *
 *  Created on: 2018. máj. 26.
 *      Author: peti
 */

#ifndef APPLICATION_MOTIONSENSOR_H_
#define APPLICATION_MOTIONSENSOR_H_

#include <stdint.h>

class MotionSensor {
public:
    class Listener {
    public:
        virtual void onPulseDetected(uint32_t index) = 0;
        virtual ~Listener() {}
    };

    MotionSensor();
    ~MotionSensor() {}
    void setListener(Listener* listener);
    void handler();

    int32_t getLastPulseTime() const;
    uint32_t getPulseCount() const;
private:
    uint32_t pulseCount;
    int32_t lastPulseTime;
    Listener* listener;
};

#endif /* APPLICATION_MOTIONSENSOR_H_ */
