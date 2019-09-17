#ifndef CHESS_ENGINE_NODE_H
#define CHESS_ENGINE_NODE_H

#include <vector>

#include "../../pieces/include/Board.h"

class Node{

    friend class PositionNode;
    friend class ValueNode;

public:
    Node();
    ~Node();
    void addChild(Node* child);

protected:
    std::vector<Node*> children;
    Node* parent;
};

#endif //CHESS_ENGINE_NODE_H
