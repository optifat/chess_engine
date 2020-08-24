#include "../include/Node.h"
#include "../../pieces/include/King_move.h"
#include "../../pieces/include/Pawn_move.h"
#include "../../pieces/include/Knight_move.h"
#include "../../pieces/include/Bishop_move.h"
#include "../../pieces/include/Rook_move.h"
#include "../../pieces/include/Queen_move.h"

#include <iostream>

Node::Node(std::shared_ptr<Node> parent, std::shared_ptr<Board> position, int layerNumber){
    this->parent = std::move(parent);
    this->position = std::move(position);
    this->positionValue = 0; // here must be evaluator
    this->layerNumber = layerNumber;
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
                for(int i = -1; i <= 1; i++){
                    for(int j = -1; j <= 1; j++){
                        int endSquare = square + 8*i + j;
                        if(endSquare < 0 || endSquare > 63 || endSquare == square){
                            continue;
                        }
                        if(King_move::makeMove(&*newPosition.get(), square, endSquare, newPosition->anotherColorCheck(endSquare))){
                            //newPosition->showBoard();
                            this->addChild(std::make_shared<Node>(shared_from_this(),
                                                                  newPosition, this->layerNumber+1));
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
                    else if(Queen_move::makeMove(&*newPosition.get(), square, endSquare, newPosition->anotherColorCheck(endSquare))){
                        //newPosition->showBoard();
                        this->addChild(std::make_shared<Node>(shared_from_this(),
                                                              newPosition, this->layerNumber+1));
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
                    else if(Queen_move::makeMove(&*newPosition.get(), square, endSquare, newPosition->anotherColorCheck(endSquare))){
                        //newPosition->showBoard();
                        this->addChild(std::make_shared<Node>(shared_from_this(),
                                                              newPosition, this->layerNumber+1));
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
                    else if(Queen_move::makeMove(&*newPosition.get(), square, endSquare, newPosition->anotherColorCheck(endSquare))){
                        //newPosition->showBoard();
                        this->addChild(std::make_shared<Node>(shared_from_this(),
                                                              newPosition, this->layerNumber+1));
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
                    else if(Queen_move::makeMove(&*newPosition.get(), square, endSquare, newPosition->anotherColorCheck(endSquare))){
                        //newPosition->showBoard();
                        this->addChild(std::make_shared<Node>(shared_from_this(),
                                                              newPosition, this->layerNumber+1));
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
                    else if(Queen_move::makeMove(&*newPosition.get(), square, endSquare, newPosition->anotherColorCheck(endSquare))){
                        //newPosition->showBoard();
                        this->addChild(std::make_shared<Node>(shared_from_this(),
                                                              newPosition, this->layerNumber+1));
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
                    else if(Queen_move::makeMove(&*newPosition.get(), square, endSquare, newPosition->anotherColorCheck(endSquare))){
                        //newPosition->showBoard();
                        this->addChild(std::make_shared<Node>(shared_from_this(),
                                                              newPosition, this->layerNumber+1));
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
                    else if(Queen_move::makeMove(&*newPosition.get(), square, endSquare, newPosition->anotherColorCheck(endSquare))){
                        //newPosition->showBoard();
                        this->addChild(std::make_shared<Node>(shared_from_this(),
                                                              newPosition, this->layerNumber+1));
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
                    else if(Queen_move::makeMove(&*newPosition.get(), square, endSquare, newPosition->anotherColorCheck(endSquare))){
                        //newPosition->showBoard();
                        this->addChild(std::make_shared<Node>(shared_from_this(),
                                                              newPosition, this->layerNumber+1));
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
                    else if(Rook_move::makeMove(&*newPosition.get(), square, endSquare, newPosition->anotherColorCheck(endSquare))){
                        //newPosition->showBoard();
                        this->addChild(std::make_shared<Node>(shared_from_this(),
                                                              newPosition, this->layerNumber+1));
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
                    else if(Rook_move::makeMove(&*newPosition.get(), square, endSquare, newPosition->anotherColorCheck(endSquare))){
                        //newPosition->showBoard();
                        this->addChild(std::make_shared<Node>(shared_from_this(),
                                                              newPosition,
                                                              this->layerNumber+1));
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
                    else if(Rook_move::makeMove(&*newPosition.get(), square, endSquare, newPosition->anotherColorCheck(endSquare))){
                        //newPosition->showBoard();
                        this->addChild(std::make_shared<Node>(shared_from_this(),
                                                              newPosition, this->layerNumber+1));
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
                    else if(Rook_move::makeMove(&*newPosition.get(), square, endSquare, newPosition->anotherColorCheck(endSquare))){
                        //newPosition->showBoard();
                        this->children.push_back(std::move(std::make_shared<Node>(shared_from_this(),
                                                              newPosition, this->layerNumber+1)));
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
                    else if(Bishop_move::makeMove(&*newPosition.get(), square, endSquare, newPosition->anotherColorCheck(endSquare))){
                        //newPosition->showBoard();
                        this->addChild(std::make_shared<Node>(shared_from_this(),
                                                              newPosition, this->layerNumber+1));
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
                    else if(Bishop_move::makeMove(&*newPosition.get(), square, endSquare, newPosition->anotherColorCheck(endSquare))){
                        //newPosition->showBoard();
                        this->addChild(std::make_shared<Node>(shared_from_this(),
                                                              newPosition, this->layerNumber+1));
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
                    else if(Bishop_move::makeMove(&*newPosition.get(), square, endSquare, newPosition->anotherColorCheck(endSquare))){
                        //newPosition->showBoard();
                        this->addChild(std::make_shared<Node>(shared_from_this(),
                                                              newPosition, this->layerNumber+1));
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
                    else if(Bishop_move::makeMove(&*newPosition.get(), square, endSquare, newPosition->anotherColorCheck(endSquare))){
                        //newPosition->showBoard();
                        this->addChild(std::make_shared<Node>(shared_from_this(),
                                                              newPosition, this->layerNumber+1));
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
                    std::cout << "Current position " << square << " " << endSquare << std::endl;
                    //newPosition->showBoard();
                    if(Move::openingPin(&*newPosition.get(), square, endSquare)){
                        continue;
                    }
                    else if(Knight_move::makeMove(&*newPosition.get(), square, endSquare, newPosition->anotherColorCheck(endSquare))){
                        std::cout << "Generated position\n";
                        std::cout << square << " " << endSquare << std::endl;
                        //newPosition->showBoard();
                        this->addChild(std::make_shared<Node>(shared_from_this(),
                                                                    newPosition, this->layerNumber+1));
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
                        std::cout << square << " " << endSquare << std::endl;
                        if(Move::openingPin(&*newPosition.get(), square, endSquare)){
                            break;
                        }
                        else if(Pawn_move::makeMove(&*newPosition.get(), square, endSquare, newPosition->anotherColorCheck(endSquare))){
                            //newPosition->showBoard();
                            this->addChild(std::make_shared<Node>(shared_from_this(),
                                                                        newPosition, this->layerNumber+1));
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
        queue.push(child);
    }
}

void Node::showBoard() {
    this->position->showBoard();
}

int Node::childrenSize() {
    return this->children.size();
}