#ifndef CHESS_ENGINE_NODE_H
#define CHESS_ENGINE_NODE_H

#include <vector>
#include <memory>

#include "../../pieces/include/Board.h"

class Node{

public:
    Node(std::shared_ptr<Node> parent, std::shared_ptr<Board> position);
    ~Node();
    void addChild(std::shared_ptr<Node> child);

private:
    std::vector<std::shared_ptr<Node>> children;
    std::shared_ptr<Node> parent;
    std::shared_ptr<Board> position;
    double positionValue;
};

#endif //CHESS_ENGINE_NODE_H
