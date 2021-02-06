#include "../include/Tree.h"
#include "../include/Evaluator.h"

#include <memory>
#include <iostream>

Tree::Tree(std::shared_ptr<Board> currentPosition) {
    this->root = std::make_shared<Node>(nullptr, std::move(currentPosition), 0);
    this->depth = 0;
    this->queue.push(this->root);
}

Tree::~Tree() {}

void Tree::generateTree(int maxDepth) {
    while(this->depth < maxDepth){
        if (this->queue.front()->currentLayer() > maxDepth){
            return;
        }
        //this->queue.front()->showBoard();
        this->queue.front()->createChildren();
        //std::cout << this->queue.front()->childrenSize() << std::endl;
        this->queue.front()->addChildrenInQueue(queue);
        this->queue.front()->updatePositionValue();
        //for(auto child: this->queue.front()->children){
        //    child->showBoard();
        //}
        this->queue.pop();
        this->depth = this->queue.front()->currentLayer();
        //std::cout << this->depth << std::endl;
    }
}

float Tree::getPositionValue() {
    return this->root->getPositionValue();
}

void Tree::optimalSequence() {
    auto current = this->root;
    for (int i = 0; i <= this->depth; i++) {
        current->showBoard();
        std::cout << std::endl;
        if (abs(current->positionValue) == MAX_POS_VAL) {
            break;
        }
        for (auto child : current->children) {
            if (child->getPositionValue() == current->getPositionValue() && 
                ((current->positionValue <= MAX_POS_VAL - 100) && current->position->whiteOrder()) || 
                ((current->positionValue >= -MAX_POS_VAL + 100) && !current->position->whiteOrder())) {
                current = child;
                break;
            }
            else if (current->position->whiteOrder() && current->positionValue > MAX_POS_VAL - 100 && 
                     child->positionValue - current->positionValue == 1) {
                current = child;
                break;
            }
            else if (!current->position->whiteOrder() && current->positionValue < -MAX_POS_VAL + 100 &&
                child->positionValue - current->positionValue == -1) {
                current = child;
                break;
            }
        }
    }
}