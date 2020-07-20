#ifndef CHESS_ENGINE_TREE_H
#define CHESS_ENGINE_TREE_H

#include <queue>
#include "Node.h"

class Tree{
public:
    Tree(std::shared_ptr<Board> currentPosition, int depth);
    ~Tree();
    void createNewLayer();

private:
    int currentDepth;
    int depth;
    std::shared_ptr<Node> root;
    std::queue<std::shared_ptr<Node>> queue;
};

#endif //CHESS_ENGINE_TREE_H