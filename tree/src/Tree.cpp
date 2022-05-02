#include "../include/Tree.h"
#include "../include/Evaluator.h"

#include <memory>
#include <iostream>

Tree::Tree(std::shared_ptr<Board> currentPosition) {
    this->root = std::make_shared<Node>(nullptr, std::move(currentPosition), 0);
    this->depth = 0;
    this->totalNodes = 1;
    this->queue.push(this->root);
}

Tree::~Tree() = default;

void Tree::generateTree(int maxDepth) {
    while(this->depth <= maxDepth){
        if (this->queue.front()->currentLayer() > maxDepth){
            return;
        }
        this->queue.front()->createChildren(this->depth != maxDepth);
        this->totalNodes += this->queue.front()->childrenSize();

        if(this->depth != maxDepth){
            this->queue.front()->addChildrenInQueue(queue);
        }

        this->queue.front()->updatePositionValue();
        this->queue.pop();
        if (this->queue.size() == 0){
            return;
        }
        this->depth = this->queue.front()->currentLayer();
    }
}

int Tree::getPositionValue() {
    return this->root->getPositionValue();
}

void Tree::optimalSequence() {
    auto current = this->root;
    current->showBoard();
    std::cout << std::endl;
    for (int i = 1; i < this->depth; i++) {
        if (abs(current->getPositionValue()) == MAX_POS_VAL) {
            break;
        }
        for (auto child : current->children) {
            if (child->getPositionValue() == current->getPositionValue() &&
                (((current->getPositionValue() <= MAX_POS_VAL - 100) && current->position->whiteOrder()) ||
                ((current->getPositionValue() >= -MAX_POS_VAL + 100) && !current->position->whiteOrder()))) {
                current = child;
                break;
            }
            else if (current->position->whiteOrder() && current->getPositionValue() > MAX_POS_VAL - 100 && 
                     child->getPositionValue() - current->getPositionValue() == 1) {
                current = child;
                break;
            }
            else if (!current->position->whiteOrder() && current->getPositionValue() < -MAX_POS_VAL + 100 &&
                child->getPositionValue() - current->getPositionValue() == -1) {
                current = child;
                break;
            }
        }
        current->showBoard();
        std::cout << std::endl;
    }
}

int Tree::totalNodesGenerated() {
    return this->totalNodes;
}