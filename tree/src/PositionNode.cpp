#include "../../pieces/include/Board.h"
#include "../include/PositionNode.h"
#include "../include/ValueNode.h"

PositionNode::PositionNode(Board* position): Node(){
    this->position = position;
}

PositionNode::~PositionNode(): ~Node() {}

void PositionNode::analyze() {
    for(int i = 0; i < this->parent->children.size(); i++){
        if(this->parent->children[i] == this){
            this->parent->children[i] = new ValueNode(0, 0, 0);
            return;
        }
    }
}
