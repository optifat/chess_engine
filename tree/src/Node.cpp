#include "../include/Node.h"
#include "../../pieces/include/King_move.h"
#include "../../pieces/include/Pawn_move.h"
#include "../../pieces/include/Knight_move.h"
#include "../../pieces/include/Bishop_move.h"
#include "../../pieces/include/Rook_move.h"
#include "../../pieces/include/Queen_move.h"

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

            if(position->kingCheck(square)){
                for(int i = -1; i <= 1; i++){
                    for(int j = -1; j <= 1; j++){
                        int endSquare = square + 8*i + j;
                        if(King_move::makeMove(&newPosition, square, endSquare, newPosition.anotherColorCheck(endSquare))){
                            Node child(static_cast<std::shared_ptr<Node>>(this), std::shared_ptr<Board>(&newPosition));
                            this->addChild(std::shared_ptr<Node>(&child));
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
                    if(Move::openingPin(&newPosition, square, endSquare)){
                        break;
                    }
                    else if(Queen_move::makeMove(&newPosition, square, endSquare, newPosition.anotherColorCheck(endSquare))){
                        Node child(static_cast<std::shared_ptr<Node>>(this), std::shared_ptr<Board>(&newPosition));
                        this->addChild(std::shared_ptr<Node>(&child));
                    }
                    else{
                        break;
                    }
                }
                for(int i = -1; i >= -7; i--){
                    int endSquare = square + i;
                    if(Move::openingPin(&newPosition, square, endSquare)){
                        break;
                    }
                    else if(Queen_move::makeMove(&newPosition, square, endSquare, newPosition.anotherColorCheck(endSquare))){
                        Node child(static_cast<std::shared_ptr<Node>>(this), std::shared_ptr<Board>(&newPosition));
                        this->addChild(std::shared_ptr<Node>(&child));
                    }
                    else{
                        break;
                    }
                }
                for(int i = 8; i <= 56; i += 8){
                    int endSquare = square + i;
                    if(Move::openingPin(&newPosition, square, endSquare)){
                        break;
                    }
                    else if(Queen_move::makeMove(&newPosition, square, endSquare, newPosition.anotherColorCheck(endSquare))){
                        Node child(static_cast<std::shared_ptr<Node>>(this), std::shared_ptr<Board>(&newPosition));
                        this->addChild(std::shared_ptr<Node>(&child));
                    }
                    else{
                        break;
                    }
                }
                for(int i = -8; i >= -56; i -= 8){
                    int endSquare = square + i;
                    if(Move::openingPin(&newPosition, square, endSquare)){
                        break;
                    }
                    else if(Queen_move::makeMove(&newPosition, square, endSquare, newPosition.anotherColorCheck(endSquare))){
                        Node child(static_cast<std::shared_ptr<Node>>(this), std::shared_ptr<Board>(&newPosition));
                        this->addChild(std::shared_ptr<Node>(&child));
                    }
                    else{
                        break;
                    }
                }
                for(int i = 7; i <= 63; i += 7){
                    int endSquare = square + i;
                    if(Move::openingPin(&newPosition, square, endSquare)){
                        break;
                    }
                    else if(Queen_move::makeMove(&newPosition, square, endSquare, newPosition.anotherColorCheck(endSquare))){
                        Node child(static_cast<std::shared_ptr<Node>>(this), std::shared_ptr<Board>(&newPosition));
                        this->addChild(std::shared_ptr<Node>(&child));
                    }
                    else{
                        break;
                    }
                }
                for(int i = -7; i >= -63; i -= 7){
                    int endSquare = square + i;
                    if(Move::openingPin(&newPosition, square, endSquare)){
                        break;
                    }
                    else if(Queen_move::makeMove(&newPosition, square, endSquare, newPosition.anotherColorCheck(endSquare))){
                        Node child(static_cast<std::shared_ptr<Node>>(this), std::shared_ptr<Board>(&newPosition));
                        this->addChild(std::shared_ptr<Node>(&child));
                    }
                    else{
                        break;
                    }
                }
                for(int i = 9; i <= 63; i += 9){
                    int endSquare = square + i;
                    if(Move::openingPin(&newPosition, square, endSquare)){
                        break;
                    }
                    else if(Queen_move::makeMove(&newPosition, square, endSquare, newPosition.anotherColorCheck(endSquare))){
                        Node child(static_cast<std::shared_ptr<Node>>(this), std::shared_ptr<Board>(&newPosition));
                        this->addChild(std::shared_ptr<Node>(&child));
                    }
                    else{
                        break;
                    }
                }
                for(int i = -9; i >= -63; i -= 9){
                    int endSquare = square + i;
                    if(Move::openingPin(&newPosition, square, endSquare)){
                        break;
                    }
                    else if(Queen_move::makeMove(&newPosition, square, endSquare, newPosition.anotherColorCheck(endSquare))){
                        Node child(static_cast<std::shared_ptr<Node>>(this), std::shared_ptr<Board>(&newPosition));
                        this->addChild(std::shared_ptr<Node>(&child));
                    }
                    else{
                        break;
                    }
                }
            }
            else if(position->rookCheck(square)){
                for(int i = 1; i <= 7; i++){
                    int endSquare = square + i;
                    if(Move::openingPin(&newPosition, square, endSquare)){
                        break;
                    }
                    else if(Rook_move::makeMove(&newPosition, square, endSquare, newPosition.anotherColorCheck(endSquare))){
                        Node child(static_cast<std::shared_ptr<Node>>(this), std::shared_ptr<Board>(&newPosition));
                        this->addChild(std::shared_ptr<Node>(&child));
                    }
                    else{
                        break;
                    }
                }
                for(int i = -1; i >= -7; i--){
                    int endSquare = square + i;
                    if(Move::openingPin(&newPosition, square, endSquare)){
                        break;
                    }
                    else if(Rook_move::makeMove(&newPosition, square, endSquare, newPosition.anotherColorCheck(endSquare))){
                        Node child(static_cast<std::shared_ptr<Node>>(this), std::shared_ptr<Board>(&newPosition));
                        this->addChild(std::shared_ptr<Node>(&child));
                    }
                    else{
                        break;
                    }
                }
                for(int i = 8; i <= 56; i += 8){
                    int endSquare = square + i;
                    if(Move::openingPin(&newPosition, square, endSquare)){
                        break;
                    }
                    else if(Rook_move::makeMove(&newPosition, square, endSquare, newPosition.anotherColorCheck(endSquare))){
                        Node child(static_cast<std::shared_ptr<Node>>(this), std::shared_ptr<Board>(&newPosition));
                        this->addChild(std::shared_ptr<Node>(&child));
                    }
                    else{
                        break;
                    }
                }
                for(int i = -8; i >= -56; i -= 8){
                    int endSquare = square + i;
                    if(Move::openingPin(&newPosition, square, endSquare)){
                        break;
                    }
                    else if(Rook_move::makeMove(&newPosition, square, endSquare, newPosition.anotherColorCheck(endSquare))){
                        Node child(static_cast<std::shared_ptr<Node>>(this), std::shared_ptr<Board>(&newPosition));
                        this->addChild(std::shared_ptr<Node>(&child));
                    }
                    else{
                        break;
                    }
                }
            }
            else if(position->bishopCheck(square)){
                for(int i = 7; i <= 63; i += 7){
                    int endSquare = square + i;
                    if(Move::openingPin(&newPosition, square, endSquare)){
                        break;
                    }
                    else if(Bishop_move::makeMove(&newPosition, square, endSquare, newPosition.anotherColorCheck(endSquare))){
                        Node child(static_cast<std::shared_ptr<Node>>(this), std::shared_ptr<Board>(&newPosition));
                        this->addChild(std::shared_ptr<Node>(&child));
                    }
                    else{
                        break;
                    }
                }
                for(int i = -7; i >= -63; i -= 7){
                    int endSquare = square + i;
                    if(Move::openingPin(&newPosition, square, endSquare)){
                        break;
                    }
                    else if(Bishop_move::makeMove(&newPosition, square, endSquare, newPosition.anotherColorCheck(endSquare))){
                        Node child(static_cast<std::shared_ptr<Node>>(this), std::shared_ptr<Board>(&newPosition));
                        this->addChild(std::shared_ptr<Node>(&child));
                    }
                    else{
                        break;
                    }
                }
                for(int i = 9; i <= 63; i += 9){
                    int endSquare = square + i;
                    if(Move::openingPin(&newPosition, square, endSquare)){
                        break;
                    }
                    else if(Bishop_move::makeMove(&newPosition, square, endSquare, newPosition.anotherColorCheck(endSquare))){
                        Node child(static_cast<std::shared_ptr<Node>>(this), std::shared_ptr<Board>(&newPosition));
                        this->addChild(std::shared_ptr<Node>(&child));
                    }
                    else{
                        break;
                    }
                }
                for(int i = -9; i >= -63; i -= 9){
                    int endSquare = square + i;
                    if(Move::openingPin(&newPosition, square, endSquare)){
                        break;
                    }
                    else if(Bishop_move::makeMove(&newPosition, square, endSquare, newPosition.anotherColorCheck(endSquare))){
                        Node child(static_cast<std::shared_ptr<Node>>(this), std::shared_ptr<Board>(&newPosition));
                        this->addChild(std::shared_ptr<Node>(&child));
                    }
                    else{
                        break;
                    }
                }
            }
            else if(position->knightCheck(square)){
                for(int delta: Knight_move::possibleKnightMoves){
                    int endSquare = square + delta;
                    if(Move::openingPin(&newPosition, square, endSquare)){
                        continue;
                    }
                    else if(Knight_move::makeMove(&newPosition, square, endSquare, newPosition.anotherColorCheck(endSquare))){
                        Node child(static_cast<std::shared_ptr<Node>>(this), std::shared_ptr<Board>(&newPosition));
                        this->addChild(std::shared_ptr<Node>(&child));
                    }
                }
            }
            else if(position->pawnCheck(square)){
                for(int i = 7; i <= 9; i++){
                    for(int j = 0; j <= 1; j++){
                        int endSquare = square + i + 8*j;
                        if(Move::openingPin(&newPosition, square, endSquare)){
                            break;
                        }
                        else if(Pawn_move::makeMove(&newPosition, square, endSquare, newPosition.anotherColorCheck(endSquare))){
                            Node child(static_cast<std::shared_ptr<Node>>(this), std::shared_ptr<Board>(&newPosition));
                            this->addChild(std::shared_ptr<Node>(&child));
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
