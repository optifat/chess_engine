#include "../include/tree.h"

Tree::Tree(Board *currentPosition, int depth = 5) {
    this->root = new PositionNode(currentPosition);
    this->depth = depth;
    this->currentDepth = 1;
    this->queue.push(this->root);
}

Tree::~Tree() {
    delete root;
}

void Tree::createNewLayer() {
    if(currentDepth == depth){
        return;
    }
    currentDepth++;

    Node* current = this->queue.front();

    while(true){                        // some condition here
        Board* newPosition = nullptr;

        //TODO create position with next move

        Node *newNode = new PositionNode(newPosition);
        this->queue.push(newNode);
    }
    this->queue.pop();
}
