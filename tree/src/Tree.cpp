#include "../include/Tree.h"

#include <memory>

Tree::Tree(std::shared_ptr<Board> currentPosition, int depth = 5) {
    this->root = std::make_shared<Node>(nullptr, std::move(currentPosition));
    this->depth = depth;
    this->currentDepth = 1;
    this->queue.push(this->root);
}

Tree::~Tree() {}

void Tree::createNewLayer() {
    if(currentDepth == depth){
        return;
    }
    currentDepth++;

    std::shared_ptr<Node> current = std::move(this->queue.front());

    while(true){                        // some condition here
        std::shared_ptr<Board> newPosition = std::make_shared<Board>();

        //TODO create position with next move

        std::shared_ptr<Node> newNode = std::make_shared<Node>(current, newPosition);
        this->queue.push(std::move(newNode));
    }
    this->queue.pop();
}
