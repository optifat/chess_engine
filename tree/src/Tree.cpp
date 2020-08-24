#include "../include/Tree.h"

#include <memory>
#include <iostream>

Tree::Tree(std::shared_ptr<Board> currentPosition) {
    this->root = std::make_shared<Node>(nullptr, std::move(currentPosition), 0);
    this->depth = 0;
    this->queue.push(this->root);
}

Tree::~Tree() {}

void Tree::generateTree(int maxDepth) {
    while(this->depth <= maxDepth){
        if (this->queue.front()->currentLayer() > maxDepth){
            return;
        }
        this->queue.front()->showBoard();
        this->depth = this->queue.front()->currentLayer();
        this->queue.front()->createChildren();
        std::cout << this->queue.front()->childrenSize() << std::endl;
        this->queue.front()->addChildrenInQueue(queue);
        for(auto child: this->queue.front()->children){
            child->showBoard();
        }
        this->queue.pop();
    }
}