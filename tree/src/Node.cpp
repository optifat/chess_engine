#include "../include/Node.h"

Node::Node() {

}

Node::~Node() {
    for(auto child: this->children){
        delete(child);
    }
    delete this;
}

void Node::addChild(Node* child) {
    this->children.push_back(child);
}
