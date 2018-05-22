/*
 * Htu21DNode.h
 *
 *  Created on: 2018. máj. 22.
 *      Author: peti
 */

#ifndef APPLICATION_HTU21D_HTU21DNODE_H_
#define APPLICATION_HTU21D_HTU21DNODE_H_

#include <mprotocol-nodes/Node.h>

class Htu21D;

class Htu21DNode: public Node {
public:
    DECLARE_PROP_FLOAT32_RO(Temperature);

    Htu21DNode(Htu21D* htu21d);
private:
    Htu21D* htu21d;
};

#endif /* APPLICATION_HTU21D_HTU21DNODE_H_ */
