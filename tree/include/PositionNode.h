#ifndef CHESS_ENGINE_POSITIONNODE_H
#define CHESS_ENGINE_POSITIONNODE_H

#include "Node.h"

class PositionNode: public Node{

public:
    PositionNode(Board* position);
    ~PositionNode();
    void analyze();
private:
    Board* position;
};


#endif //CHESS_ENGINE_POSITIONNODE_H
