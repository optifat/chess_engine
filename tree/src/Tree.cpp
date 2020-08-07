#include "../include/Tree.h"

#include <memory>
#include <iostream>

Tree::Tree(std::shared_ptr<Board> currentPosition) {
    this->root = std::make_shared<Node>(nullptr, std::move(currentPosition), 0);
    this->depth = 0;
    this->queue.push(this->root);
}

Tree::~Tree() {}

/*void Tree::createNewLayer() {
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
        break;
    }
    this->queue.pop();
}*/

void Tree::generateTree(int maxDepth) {
    //while(this->depth <= maxDepth){
        if (this->queue.front()->currentLayer() > maxDepth){
            return;
        }
        this->queue.front()->showBoard();
        this->depth = this->queue.front()->currentLayer();
        this->queue.front()->createChildren();
        std::cout << this->queue.front()->childrenSize() << std::endl;
    for(auto child: queue.front()->children){
        child->showBoard();
        std::cout << std::endl;
    }
        this->queue.front()->addChildrenInQueue(queue);
        this->queue.pop();
    //}
}