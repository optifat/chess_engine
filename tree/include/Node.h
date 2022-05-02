#ifndef CHESS_ENGINE_NODE_H
#define CHESS_ENGINE_NODE_H

#include <vector>
#include <memory>
#include <queue>
#include <optional>

#include "../../pieces/include/Board.h"

class Node: public std::enable_shared_from_this<Node>{

    friend class Tree;
    friend class Evaluator;

public:
    Node(std::shared_ptr<Node> parent, std::shared_ptr<Board> position, int layerNumber);
    ~Node();
    void createChildren(bool addingChildren);
    int currentLayer();
    void addChildrenInQueue(std::queue<std::shared_ptr<Node>> &queue);
    void showBoard();
    int childrenSize();
    int getPositionValue();
    void updatePositionValue();

private:
    void addChild(std::shared_ptr<Node> child);
    void updateParentsPositionValue();

    std::vector<std::shared_ptr<Node>> children;
    std::weak_ptr<Node> parent;
    std::shared_ptr<Board> position;
    std::optional<int> positionValue;
    int layerNumber;
    bool evaluated;
    bool hasChildren;
};

#endif //CHESS_ENGINE_NODE_H
