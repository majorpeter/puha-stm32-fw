/*
 * Htu21DNode.h
 *
 *  Created on: 2018. máj. 22.
 *      Author: peti
 */

#ifndef APPLICATION_HTU21D_HTU21DNODE_H_
#define APPLICATION_HTU21D_HTU21DNODE_H_

#include <mprotocol-nodes/Node.h>
#include "Htu21D.h"

class Htu21DNode: public Node, private Htu21D::Listener {
public:
    DECLARE_PROP_FLOAT32_RO(Temperature);
    DECLARE_PROP_FLOAT32_RO(Humidity);

    Htu21DNode(Htu21D* htu21d);
private:
    Htu21D* htu21d;

    virtual void onTemperatureChanged(float temperature);
    virtual void onHumidityChanged(float humidity);
};

#endif /* APPLICATION_HTU21D_HTU21DNODE_H_ */
