#include "../include/ValueNode.h"

ValueNode::ValueNode(int initSquare, int endSquare, int value): Node() {
    this->initSquare = initSquare;
    this->endSquare = endSquare;
    this->positionValue = value;
}

ValueNode::~ValueNode(): ~Node(){}
