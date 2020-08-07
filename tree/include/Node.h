#ifndef CHESS_ENGINE_NODE_H
#define CHESS_ENGINE_NODE_H

#include <vector>
#include <memory>
#include <queue>

#include "../../pieces/include/Board.h"

class Node{

public:
    Node(std::shared_ptr<Node> parent, std::shared_ptr<Board> position, int layerNumber);
    ~Node();
    void createChildren();
    int currentLayer();
    void addChildrenInQueue(std::queue<std::shared_ptr<Node>> &queue);
    void showBoard();

private:
    void addChild(std::shared_ptr<Node> child);

    std::vector<std::shared_ptr<Node>> children;
    std::shared_ptr<Node> parent;
    std::shared_ptr<Board> position;
    double positionValue;
    int layerNumber;
};

#endif //CHESS_ENGINE_NODE_H
