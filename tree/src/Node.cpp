#include "../include/Node.h"

Node::Node(std::shared_ptr<Node> parent, std::shared_ptr<Board> position){
    this->parent = std::move(parent);
    this->position = std::move(position);
    this->positionValue = 0; // here must be evaluator
}

Node::~Node() = default;

void Node::addChild(std::shared_ptr<Node> child) {
    this->children.push_back(std::move(child));
}

void Node::createChildren() {
    for(int square = 0; square <= 63; square++){
        if(position->currentColorCheck(square)){

            Board newPosition = *position.get();
            Node child(static_cast<std::shared_ptr<Node>>(this), std::shared_ptr<Board>(&newPosition));
            this->addChild(std::shared_ptr<Node>(&child));

            if(position->kingCheck(square)){
                continue;
            }else if(position->queenCheck(square)){
                continue;
            }else if(position->rookCheck(square)){
                continue;
            }else if(position->bishopCheck(square)){
                continue;
            }else if(position->knightCheck(square)){
                continue;
            }else if(position->pawnCheck(square)){
                continue;
            }
        }
    }
}
