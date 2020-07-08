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
