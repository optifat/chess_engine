#ifndef CHESS_ENGINE_VALUENODE_H
#define CHESS_ENGINE_VALUENODE_H

#include "Node.h"

class ValueNode: public Node{

public:
    ValueNode(int initSquare, int endSquare, int value);
    ~ValueNode();

private:
    float positionValue;
    int initSquare;
    int endSquare;
};


#endif //CHESS_ENGINE_VALUENODE_H
