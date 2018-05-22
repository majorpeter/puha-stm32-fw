/*
 * SystemNode.h
 *
 *  Created on: 2018. jan. 7.
 *      Author: peti
 */

#ifndef APPLICATION_SYSTEMNODE_H_
#define APPLICATION_SYSTEMNODE_H_

#include <mprotocol-nodes/Node.h>

class SystemNode: public Node {
public:
    DECLARE_PROP_METHOD(reset);
    DECLARE_PROP_INT32_RO(TimeMs);

    SystemNode();
};

#endif /* APPLICATION_SYSTEMNODE_H_ */
