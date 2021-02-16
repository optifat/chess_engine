#include "../include/Node.h"
#include "../include/Evaluator.h"
#include "../../pieces/include/King_move.h"
#include "../../pieces/include/Pawn_move.h"
#include "../../pieces/include/Knight_move.h"
#include "../../pieces/include/Bishop_move.h"
#include "../../pieces/include/Rook_move.h"
#include "../../pieces/include/Queen_move.h"
#include "../../pieces/include/Castling.h"

#include <iostream>

Node::Node(std::shared_ptr<Node> parent, std::shared_ptr<Board> position, int layerNumber){
    this->parent = std::move(parent);
    this->position = std::move(position);
    this->positionValue = Evaluator::evaluatePosition(*this->position.get());
    this->layerNumber = layerNumber;
    //this->updateParentsPositionValue();
}

Node::~Node() = default;

void Node::addChild(std::shared_ptr<Node> child) {
    this->children.push_back(std::move(child));
}

void Node::createChildren() {
    for(int square = 0; square <= 63; square++){
        if(position->currentColorCheck(square)){

            std::shared_ptr<Board> newPosition = std::make_shared<Board>(*position.get());

            if(position->kingCheck(square)){
                if (position->whiteOrder() && square == 4) {
                    if (Castling::makeMove(&*newPosition.get(), square, square + 2)) {
                        this->addChild(std::make_shared<Node>(shared_from_this(),
                            newPosition, this->layerNumber + 1));
                        newPosition = std::make_shared<Board>(*position.get());
                    }
                    if (Castling::makeMove(&*newPosition.get(), square, square - 2)) {
                        this->addChild(std::make_shared<Node>(shared_from_this(),
                            newPosition, this->layerNumber + 1));
                        newPosition = std::make_shared<Board>(*position.get());
                    }
                }
                else if(!position->whiteOrder() && square == 60) {
                    if (Castling::makeMove(&*newPosition.get(), square, square + 2)) {
                        this->addChild(std::make_shared<Node>(shared_from_this(),
                            newPosition, this->layerNumber + 1));
                        newPosition = std::make_shared<Board>(*position.get());
                    }
                    if (Castling::makeMove(&*newPosition.get(), square, square - 2)) {
                        this->addChild(std::make_shared<Node>(shared_from_this(),
                            newPosition, this->layerNumber + 1));
                        newPosition = std::make_shared<Board>(*position.get());
                    }
                }
                
                for(int i = -1; i <= 1; i++){
                    for(int j = -1; j <= 1; j++){
                        int endSquare = square + 8*i + j;
                        if(endSquare < 0 || endSquare > 63 || endSquare == square){
                            continue;
                        }
                        if(King_move::makeMove(&*newPosition.get(), square, endSquare)){
                            if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                                //newPosition->showBoard();
                                this->addChild(std::make_shared<Node>(shared_from_this(),
                                               newPosition, this->layerNumber + 1));
                            }
                            newPosition = std::make_shared<Board>(*position.get());
                        }
                    }
                }
            }
            else if(position->queenCheck(square)){
                /*
                 * If queen can't move to some square in some direction, it couldn't go further either
                 * We consider every direction separately so we won't have to check all the impossible moves
                 * This is also true for rooks, bishops and first pawn move (like e2-e4)
                 */
                for(int i = 1; i <= 7; i++){
                    int endSquare = square + i;
                    if(endSquare > 63){
                        break;
                    }
                    if(Move::openingPin(&*newPosition.get(), square, endSquare)){
                        break;
                    }
                    else if(Queen_move::makeMove(&*newPosition.get(), square, endSquare)){
                        if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                            //newPosition->showBoard();
                            this->addChild(std::make_shared<Node>(shared_from_this(),
                                           newPosition, this->layerNumber + 1));
                        }
                        newPosition = std::make_shared<Board>(*position.get());
                    }
                    else{
                        break;
                    }
                }
                for(int i = -1; i >= -7; i--){
                    int endSquare = square + i;
                    if(endSquare < 0){
                        break;
                    }
                    if(Move::openingPin(&*newPosition.get(), square, endSquare)){
                        break;
                    }
                    else if(Queen_move::makeMove(&*newPosition.get(), square, endSquare)){
                        if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                            //newPosition->showBoard();
                            this->addChild(std::make_shared<Node>(shared_from_this(),
                                           newPosition, this->layerNumber + 1));
                        }
                        newPosition = std::make_shared<Board>(*position.get());
                    }
                    else{
                        break;
                    }
                }
                for(int i = 8; i <= 56; i += 8){
                    int endSquare = square + i;
                    if(endSquare > 63){
                        break;
                    }
                    if(Move::openingPin(&*newPosition.get(), square, endSquare)){
                        break;
                    }
                    else if(Queen_move::makeMove(&*newPosition.get(), square, endSquare)){
                        if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                            //newPosition->showBoard();
                            this->addChild(std::make_shared<Node>(shared_from_this(),
                                           newPosition, this->layerNumber + 1));
                        }
                        newPosition = std::make_shared<Board>(*position.get());
                    }
                    else{
                        break;
                    }
                }
                for(int i = -8; i >= -56; i -= 8){
                    int endSquare = square + i;
                    if(endSquare < 0){
                        break;
                    }
                    if(Move::openingPin(&*newPosition.get(), square, endSquare)){
                        break;
                    }
                    else if(Queen_move::makeMove(&*newPosition.get(), square, endSquare)){
                        if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                            //newPosition->showBoard();
                            this->addChild(std::make_shared<Node>(shared_from_this(),
                                           newPosition, this->layerNumber + 1));
                        }
                        newPosition = std::make_shared<Board>(*position.get());
                    }
                    else{
                        break;
                    }
                }
                for(int i = 7; i <= 63; i += 7){
                    int endSquare = square + i;
                    if(endSquare > 63){
                        break;
                    }
                    if(Move::openingPin(&*newPosition.get(), square, endSquare)){
                        break;
                    }
                    else if(Queen_move::makeMove(&*newPosition.get(), square, endSquare)){
                        if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                            //newPosition->showBoard();
                            this->addChild(std::make_shared<Node>(shared_from_this(),
                                           newPosition, this->layerNumber + 1));
                        }
                        newPosition = std::make_shared<Board>(*position.get());
                    }
                    else{
                        break;
                    }
                }
                for(int i = -7; i >= -63; i -= 7){
                    int endSquare = square + i;
                    if(endSquare < 0){
                        break;
                    }
                    if(Move::openingPin(&*newPosition.get(), square, endSquare)){
                        break;
                    }
                    else if(Queen_move::makeMove(&*newPosition.get(), square, endSquare)){
                        if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                            //newPosition->showBoard();
                            this->addChild(std::make_shared<Node>(shared_from_this(),
                                           newPosition, this->layerNumber + 1));
                        }
                        newPosition = std::make_shared<Board>(*position.get());
                    }
                    else{
                        break;
                    }
                }
                for(int i = 9; i <= 63; i += 9){
                    int endSquare = square + i;
                    if(endSquare > 63){
                        break;
                    }
                    if(Move::openingPin(&*newPosition.get(), square, endSquare)){
                        break;
                    }
                    else if(Queen_move::makeMove(&*newPosition.get(), square, endSquare)){
                        if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                            //newPosition->showBoard();
                            this->addChild(std::make_shared<Node>(shared_from_this(),
                                           newPosition, this->layerNumber + 1));
                        }
                        newPosition = std::make_shared<Board>(*position.get());
                    }
                    else{
                        break;
                    }
                }
                for(int i = -9; i >= -63; i -= 9){
                    int endSquare = square + i;
                    if(endSquare < 0){
                        break;
                    }
                    if(Move::openingPin(&*newPosition.get(), square, endSquare)){
                        break;
                    }
                    else if(Queen_move::makeMove(&*newPosition.get(), square, endSquare)){
                        if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                            //newPosition->showBoard();
                            this->addChild(std::make_shared<Node>(shared_from_this(),
                                           newPosition, this->layerNumber + 1));
                        }
                        newPosition = std::make_shared<Board>(*position.get());
                    }
                    else{
                        break;
                    }
                }
            }
            else if(position->rookCheck(square)){
                for(int i = 1; i <= 7; i++){
                    int endSquare = square + i;
                    if(endSquare > 63){
                        break;
                    }
                    if(Move::openingPin(&*newPosition.get(), square, endSquare)){
                        break;
                    }
                    else if(Rook_move::makeMove(&*newPosition.get(), square, endSquare)){
                        if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                            //newPosition->showBoard();
                            this->addChild(std::make_shared<Node>(shared_from_this(),
                                           newPosition, this->layerNumber + 1));
                        }
                        newPosition = std::make_shared<Board>(*position.get());
                    }
                    else{
                        break;
                    }
                }
                for(int i = -1; i >= -7; i--){
                    int endSquare = square + i;
                    if(endSquare < 0){
                        break;
                    }
                    if(Move::openingPin(&*newPosition.get(), square, endSquare)){
                        break;
                    }
                    else if(Rook_move::makeMove(&*newPosition.get(), square, endSquare)){
                        if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                            //newPosition->showBoard();
                            this->addChild(std::make_shared<Node>(shared_from_this(),
                                           newPosition, this->layerNumber + 1));
                        }
                        newPosition = std::make_shared<Board>(*position.get());
                    }
                    else{
                        break;
                    }
                }
                for(int i = 8; i <= 56; i += 8){
                    int endSquare = square + i;
                    if(endSquare > 63){
                        break;
                    }
                    if(Move::openingPin(&*newPosition.get(), square, endSquare)){
                        break;
                    }
                    else if(Rook_move::makeMove(&*newPosition.get(), square, endSquare)){
                        if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                            //newPosition->showBoard();
                            this->addChild(std::make_shared<Node>(shared_from_this(),
                                           newPosition, this->layerNumber + 1));
                        }
                        newPosition = std::make_shared<Board>(*position.get());
                    }
                    else{
                        break;
                    }
                }
                for(int i = -8; i >= -56; i -= 8){
                    int endSquare = square + i;
                    if(endSquare < 0){
                        break;
                    }
                    if(Move::openingPin(&*newPosition.get(), square, endSquare)){
                        break;
                    }
                    else if(Rook_move::makeMove(&*newPosition.get(), square, endSquare)){
                        if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                            //newPosition->showBoard();
                            this->addChild(std::make_shared<Node>(shared_from_this(),
                                           newPosition, this->layerNumber + 1));
                        }
                        newPosition = std::make_shared<Board>(*position.get());
                    }
                    else{
                        break;
                    }
                }
            }
            else if(position->bishopCheck(square)){
                for(int i = 7; i <= 63; i += 7){
                    int endSquare = square + i;
                    if(endSquare > 63){
                        break;
                    }
                    if(Move::openingPin(&*newPosition.get(), square, endSquare)){
                        break;
                    }
                    else if(Bishop_move::makeMove(&*newPosition.get(), square, endSquare)){
                        if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                            //newPosition->showBoard();
                            this->addChild(std::make_shared<Node>(shared_from_this(),
                                           newPosition, this->layerNumber + 1));
                        }
                        newPosition = std::make_shared<Board>(*position.get());
                    }
                    else{
                        break;
                    }
                }
                for(int i = -7; i >= -63; i -= 7){
                    int endSquare = square + i;
                    if(endSquare < 0){
                        break;
                    }
                    if(Move::openingPin(&*newPosition.get(), square, endSquare)){
                        break;
                    }
                    else if(Bishop_move::makeMove(&*newPosition.get(), square, endSquare)){
                        if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                            //newPosition->showBoard();
                            this->addChild(std::make_shared<Node>(shared_from_this(),
                                           newPosition, this->layerNumber + 1));
                        }
                        newPosition = std::make_shared<Board>(*position.get());
                    }
                    else{
                        break;
                    }
                }
                for(int i = 9; i <= 63; i += 9){
                    int endSquare = square + i;
                    if(endSquare > 63){
                        break;
                    }
                    if(Move::openingPin(&*newPosition.get(), square, endSquare)){
                        break;
                    }
                    else if(Bishop_move::makeMove(&*newPosition.get(), square, endSquare)){
                        if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                            //newPosition->showBoard();
                            this->addChild(std::make_shared<Node>(shared_from_this(),
                                           newPosition, this->layerNumber + 1));
                        }
                        newPosition = std::make_shared<Board>(*position.get());
                    }
                    else{
                        break;
                    }
                }
                for(int i = -9; i >= -63; i -= 9){
                    int endSquare = square + i;
                    if(endSquare < 0){
                        break;
                    }
                    if(Move::openingPin(&*newPosition.get(), square, endSquare)){
                        break;
                    }
                    else if(Bishop_move::makeMove(&*newPosition.get(), square, endSquare)){
                        if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                            //newPosition->showBoard();
                            this->addChild(std::make_shared<Node>(shared_from_this(),
                                           newPosition, this->layerNumber + 1));
                        }
                        newPosition = std::make_shared<Board>(*position.get());
                    }
                    else{
                        break;
                    }
                }
            }
            else if(position->knightCheck(square)){
                for(int delta: Knight_move::possibleKnightMoves){
                    int endSquare = square + delta;
                    if(endSquare < 0 || endSquare > 63){
                        continue;
                    }
                    //newPosition->showBoard();
                    if(Move::openingPin(&*newPosition.get(), square, endSquare)){
                        continue;
                    }
                    else if(Knight_move::makeMove(&*newPosition.get(), square, endSquare)){
                        if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                            //newPosition->showBoard();
                            this->addChild(std::make_shared<Node>(shared_from_this(),
                                           newPosition, this->layerNumber + 1));
                        }
                        newPosition = std::make_shared<Board>(*position.get());
                    }
                }
            }
            else if(position->pawnCheck(square)){
                for(int i = 7; i <= 9; i++){
                    for(int j = 0; j <= 1; j++){
                        int endSquare = square + (i + 8*j)*(-1+2*position->whiteOrder());
                        if(endSquare > 63 || endSquare < 0){
                            break;
                        }
                        if(Move::openingPin(&*newPosition.get(), square, endSquare)){
                            break;
                        }
                        else if (endSquare / 8 == 0 || endSquare / 8 == 7) {
                            std::vector<char> possiblePromotion = {'Q', 'R', 'B', 'N'};
                            for (char promotion : possiblePromotion) {
                                if (Pawn_move::makeMove(&*newPosition.get(), square, endSquare, i != 8 , promotion)) {
                                    if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                                        //newPosition->showBoard();
                                        this->addChild(std::make_shared<Node>(shared_from_this(),
                                            newPosition, this->layerNumber + 1));
                                    }
                                    newPosition = std::make_shared<Board>(*position.get());
                                }
                                else {
                                    break;
                                }
                            }
                        }
                        else if(Pawn_move::makeMove(&*newPosition.get(), square, endSquare, i != 8)){
                            if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                                //newPosition->showBoard();
                                this->addChild(std::make_shared<Node>(shared_from_this(),
                                               newPosition, this->layerNumber + 1));
                            }
                            newPosition = std::make_shared<Board>(*position.get());
                        }

                        else{
                            break;
                        }
                    }
                }
            }
        }
    }
}

int Node::currentLayer(){
    return this->layerNumber;
}

void Node::addChildrenInQueue(std::queue<std::shared_ptr<Node>> &queue){
    for(auto child: this->children){
        if (abs(child->positionValue) != MAX_POS_VAL) {
            queue.push(child);
        }
    }
}

void Node::showBoard() {
    this->position->showBoard();
}

int Node::childrenSize() {
    return this->children.size();
}

void Node::updateParentsPositionValue() {
    if (this->layerNumber == 0) {
        return;
    }
    else if(this->parent.lock()->positionValue > this->positionValue && this->parent.lock()->position->whiteOrder()){
        return;
    }
    else if(this->parent.lock()->positionValue < this->positionValue && !this->parent.lock()->position->whiteOrder()){
        return;
    }
    this->parent.lock()->positionValue = this->positionValue;
    this->parent.lock()->updateParentsPositionValue();
}

void Node::updatePositionValue() {
    float val;
    if (this->position->whiteOrder()) {
        val = (this->childrenSize() == 0 && abs(this->positionValue) != MAX_POS_VAL) ? 0 : -MAX_POS_VAL;
        for (auto child : this->children) {
            float childValue = child->positionValue > MAX_POS_VAL - 100 ? child->positionValue-1 : child->positionValue;
            val = val > childValue ? val : childValue;
        }
    }
    else {
        val = (this->childrenSize() == 0 && abs(this->positionValue) != MAX_POS_VAL) ? 0 : MAX_POS_VAL;
        for (auto child : this->children) {
            float childValue = child->positionValue < -MAX_POS_VAL + 100 ? child->positionValue+1 : child->positionValue;
            val = val < childValue ? val : childValue;
        }
    }
    this->positionValue = val;
    // this->updateParentsPositionValue();
    if (this->layerNumber != 0) {
        this->parent.lock()->updatePositionValue();
    }
}

float Node::getPositionValue() {
    return this->positionValue;
}