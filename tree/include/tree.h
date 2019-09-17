#ifndef CHESS_ENGINE_TREE_H
#define CHESS_ENGINE_TREE_H

#include <queue>
#include "Node.h"
#include "PositionNode.h"
#include "ValueNode.h"

class Tree{
public:
    Tree(Board* currentPosition, int depth);
    ~Tree();
    void createNewLayer();

private:
    int currentDepth;
    int depth;
    Node* root;
    std::queue<Node*> queue;
};

#endif //CHESS_ENGINE_TREE_H
