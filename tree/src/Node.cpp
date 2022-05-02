#ifdef _MSC_VER
#  include <intrin.h>
#  define ctz(x) (63-__lzcnt64(x))
#  define popcount __popcnt64
#endif

#ifdef __GNUC__
#  define ctz(x) x?__builtin_ctzl(x):63
#  define popcount __builtin_popcountl
#endif

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
    this->evaluated = false;
    this->positionValue = std::nullopt;
    this->layerNumber = layerNumber;
}

Node::~Node() = default;

void Node::addChild(std::shared_ptr<Node> child) {
    this->children.push_back(std::move(child));
}

void Node::createChildren(bool addingChildren) {
    std::shared_ptr<Board> newPosition = std::make_shared<Board>(std::move(*position.get()));
    int square = this->position->currentColorKingPosition();
    if (position->whiteOrder() && square == 4) {
        if (Castling::makeMove(*newPosition.get(), square, square + 2)) {
            this->hasChildren = true;
            if(!addingChildren){
                return;
            }
            this->addChild(std::move(std::make_shared<Node>(shared_from_this(),
                                                  std::move(newPosition), this->layerNumber + 1)));
            newPosition = std::make_shared<Board>(std::move(*position.get()));
        }
        if (Castling::makeMove(*newPosition.get(), square, square - 2)) {
            this->hasChildren = true;
            if(!addingChildren){
                return;
            }
            this->addChild(std::move(std::make_shared<Node>(shared_from_this(),
                                                  std::move(newPosition), this->layerNumber + 1)));
            newPosition = std::make_shared<Board>(std::move(*position.get()));
        }
    }
    else if(!position->whiteOrder() && square == 60) {
        if (Castling::makeMove(*newPosition.get(), square, square + 2)) {
            this->hasChildren = true;
            if(!addingChildren){
                return;
            }
            this->addChild(std::move(std::make_shared<Node>(shared_from_this(),
                                                  std::move(newPosition), this->layerNumber + 1)));
            newPosition = std::make_shared<Board>(std::move(*position.get()));
        }
        if (Castling::makeMove(*newPosition.get(), square, square - 2)) {
            this->hasChildren = true;
            if(!addingChildren){
                return;
            }
            this->addChild(std::move(std::make_shared<Node>(shared_from_this(),
                                                  std::move(newPosition), this->layerNumber + 1)));
            newPosition = std::make_shared<Board>(std::move(*position.get()));
        }
    }

    int endSquare;

    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
            endSquare = square + 8*i + j;
            if(endSquare < 0 || endSquare > 63 || endSquare == square){
                continue;
            }
            if(King_move::makeMove(*newPosition.get(), square, endSquare)){
                if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                    this->hasChildren = true;
                    if(!addingChildren){
                        return;
                    }
                    this->addChild(std::move(std::make_shared<Node>(shared_from_this(),
                                                          std::move(newPosition), this->layerNumber + 1)));
                }
                newPosition = std::make_shared<Board>(std::move(*position.get()));
            }
        }
    }

    auto currentColorQueens = position->currentColor() & position->queens;
    auto totalQueenNumber = popcount(currentColorQueens);
    for(int queenNumber = 0; queenNumber < totalQueenNumber; queenNumber++) {
        square = ctz(currentColorQueens);
        /*
         * If queen can't move to some square in some direction, it couldn't go further either
         * We consider every direction separately so we won't have to check all the impossible moves
         * This is also true for rooks, bishops and first pawn move (like e2-e4)
         */
        for(int i = 1; i <= 7; i++){
            endSquare = square + i;
            if(endSquare > 63){
                break;
            }
            if(Move::openingPin(*newPosition.get(), square, endSquare)){
                break;
            }
            else if(Queen_move::makeMove(*newPosition.get(), square, endSquare)){
                if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                    this->hasChildren = true;
                    if(!addingChildren){
                        return;
                    }
                    this->addChild(std::move(std::make_shared<Node>(shared_from_this(),
                                                          std::move(newPosition), this->layerNumber + 1)));
                }
                newPosition = std::make_shared<Board>(std::move(*position.get()));
            }
            else{
                break;
            }
        }
        for(int i = -1; i >= -7; i--){
            endSquare = square + i;
            if(endSquare < 0){
                break;
            }
            if(Move::openingPin(*newPosition.get(), square, endSquare)){
                break;
            }
            else if(Queen_move::makeMove(*newPosition.get(), square, endSquare)){
                if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                    this->hasChildren = true;
                    if(!addingChildren){
                        return;
                    }
                    this->addChild(std::move(std::make_shared<Node>(shared_from_this(),
                                                          std::move(newPosition), this->layerNumber + 1)));
                }
                newPosition = std::make_shared<Board>(std::move(*position.get()));
            }
            else{
                break;
            }
        }
        for(int i = 8; i <= 56; i += 8){
            endSquare = square + i;
            if(endSquare > 63){
                break;
            }
            if(Move::openingPin(*newPosition.get(), square, endSquare)){
                break;
            }
            else if(Queen_move::makeMove(*newPosition.get(), square, endSquare)){
                if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                    this->hasChildren = true;
                    if(!addingChildren){
                        return;
                    }
                    this->addChild(std::move(std::make_shared<Node>(shared_from_this(),
                                                          std::move(newPosition), this->layerNumber + 1)));
                }
                newPosition = std::make_shared<Board>(std::move(*position.get()));
            }
            else{
                break;
            }
        }
        for(int i = -8; i >= -56; i -= 8){
            endSquare = square + i;
            if(endSquare < 0){
                break;
            }
            if(Move::openingPin(*newPosition.get(), square, endSquare)){
                break;
            }
            else if(Queen_move::makeMove(*newPosition.get(), square, endSquare)){
                if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                    this->hasChildren = true;
                    if(!addingChildren){
                        return;
                    }
                    this->addChild(std::move(std::make_shared<Node>(shared_from_this(),
                                                          std::move(newPosition), this->layerNumber + 1)));
                }
                newPosition = std::make_shared<Board>(std::move(*position.get()));
            }
            else{
                break;
            }
        }
        for(int i = 7; i <= 63; i += 7){
            endSquare = square + i;
            if(endSquare > 63){
                break;
            }
            if(Move::openingPin(*newPosition.get(), square, endSquare)){
                break;
            }
            else if(Queen_move::makeMove(*newPosition.get(), square, endSquare)){
                if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                    this->hasChildren = true;
                    if(!addingChildren){
                        return;
                    }
                    this->addChild(std::move(std::make_shared<Node>(shared_from_this(),
                                                          std::move(newPosition), this->layerNumber + 1)));
                }
                newPosition = std::make_shared<Board>(std::move(*position.get()));
            }
            else{
                break;
            }
        }
        for(int i = -7; i >= -63; i -= 7){
            endSquare = square + i;
            if(endSquare < 0){
                break;
            }
            if(Move::openingPin(*newPosition.get(), square, endSquare)){
                break;
            }
            else if(Queen_move::makeMove(*newPosition.get(), square, endSquare)){
                if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                    this->hasChildren = true;
                    if(!addingChildren){
                        return;
                    }
                    this->addChild(std::move(std::make_shared<Node>(shared_from_this(),
                                                          std::move(newPosition), this->layerNumber + 1)));
                }
                newPosition = std::make_shared<Board>(std::move(*position.get()));
            }
            else{
                break;
            }
        }
        for(int i = 9; i <= 63; i += 9){
            endSquare = square + i;
            if(endSquare > 63){
                break;
            }
            if(Move::openingPin(*newPosition.get(), square, endSquare)){
                break;
            }
            else if(Queen_move::makeMove(*newPosition.get(), square, endSquare)){
                if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                    this->hasChildren = true;
                    if(!addingChildren){
                        return;
                    }
                    this->addChild(std::move(std::make_shared<Node>(shared_from_this(),
                                                          std::move(newPosition), this->layerNumber + 1)));
                }
                newPosition = std::make_shared<Board>(std::move(*position.get()));
            }
            else{
                break;
            }
        }
        for(int i = -9; i >= -63; i -= 9){
            endSquare = square + i;
            if(endSquare < 0){
                break;
            }
            if(Move::openingPin(*newPosition.get(), square, endSquare)){
                break;
            }
            else if(Queen_move::makeMove(*newPosition.get(), square, endSquare)){
                if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                    this->hasChildren = true;
                    if(!addingChildren){
                        return;
                    }
                    this->addChild(std::move(std::make_shared<Node>(shared_from_this(),
                                                          std::move(newPosition), this->layerNumber + 1)));
                }
                newPosition = std::make_shared<Board>(std::move(*position.get()));
            }
            else{
                break;
            }
        }
        currentColorQueens &= ~((uint64_t)1 << square);
    }

    auto currentColorRooks = (position->currentColor() & position->rooks);
    auto totalRookNumber = popcount(currentColorRooks);
    for(int rookNumber = 0; rookNumber < totalRookNumber; rookNumber++) {
        square = ctz(currentColorRooks);
        for(int i = 1; i <= 7; i++){
            endSquare = square + i;
            if(endSquare > 63){
                break;
            }
            if(Move::openingPin(*newPosition.get(), square, endSquare)){
                break;
            }
            else if(Rook_move::makeMove(*newPosition.get(), square, endSquare)){
                if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                    this->hasChildren = true;
                    if(!addingChildren){
                        return;
                    }
                    this->addChild(std::move(std::make_shared<Node>(shared_from_this(),
                                                          std::move(newPosition), this->layerNumber + 1)));
                }
                newPosition = std::make_shared<Board>(std::move(*position.get()));
            }
            else{
                break;
            }
        }
        for(int i = -1; i >= -7; i--){
            endSquare = square + i;
            if(endSquare < 0){
                break;
            }
            if(Move::openingPin(*newPosition.get(), square, endSquare)){
                break;
            }
            else if(Rook_move::makeMove(*newPosition.get(), square, endSquare)){
                if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                    this->hasChildren = true;
                    if(!addingChildren){
                        return;
                    }
                    this->addChild(std::move(std::make_shared<Node>(shared_from_this(),
                                                          std::move(newPosition), this->layerNumber + 1)));
                }
                newPosition = std::make_shared<Board>(std::move(*position.get()));
            }
            else{
                break;
            }
        }
        for(int i = 8; i <= 56; i += 8){
            endSquare = square + i;
            if(endSquare > 63){
                break;
            }
            if(Move::openingPin(*newPosition.get(), square, endSquare)){
                break;
            }
            else if(Rook_move::makeMove(*newPosition.get(), square, endSquare)){
                if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                    this->hasChildren = true;
                    if(!addingChildren){
                        return;
                    }
                    this->addChild(std::move(std::make_shared<Node>(shared_from_this(),
                                                          std::move(newPosition), this->layerNumber + 1)));
                }
                newPosition = std::make_shared<Board>(std::move(*position.get()));
            }
            else{
                break;
            }
        }
        for(int i = -8; i >= -56; i -= 8){
            endSquare = square + i;
            if(endSquare < 0){
                break;
            }
            if(Move::openingPin(*newPosition.get(), square, endSquare)){
                break;
            }
            else if(Rook_move::makeMove(*newPosition.get(), square, endSquare)){
                if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                    this->hasChildren = true;
                    if(!addingChildren){
                        return;
                    }
                    this->addChild(std::move(std::make_shared<Node>(shared_from_this(),
                                                          std::move(newPosition), this->layerNumber + 1)));
                }
                newPosition = std::make_shared<Board>(std::move(*position.get()));
            }
            else{
                break;
            }
        }
        currentColorRooks &= ~((uint64_t)1 << square);
    }

    auto currentColorBishops = (position->currentColor() & position->bishops);
    auto totalBishopNumber = popcount(currentColorBishops);
    for(int bishopNumber = 0; bishopNumber < totalBishopNumber; bishopNumber++) {
        square = ctz(currentColorBishops);
        for(int i = 7; i <= 63; i += 7){
            endSquare = square + i;
            if(endSquare > 63){
                break;
            }
            if(Move::openingPin(*newPosition.get(), square, endSquare)){
                break;
            }
            else if(Bishop_move::makeMove(*newPosition.get(), square, endSquare)){
                if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                    this->hasChildren = true;
                    if(!addingChildren){
                        return;
                    }
                    this->addChild(std::move(std::make_shared<Node>(shared_from_this(),
                                                          std::move(newPosition), this->layerNumber + 1)));
                }
                newPosition = std::make_shared<Board>(std::move(*position.get()));
            }
            else{
                break;
            }
        }
        for(int i = -7; i >= -63; i -= 7){
            endSquare = square + i;
            if(endSquare < 0){
                break;
            }
            if(Move::openingPin(*newPosition.get(), square, endSquare)){
                break;
            }
            else if(Bishop_move::makeMove(*newPosition.get(), square, endSquare)){
                if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                    this->hasChildren = true;
                    if(!addingChildren){
                        return;
                    }
                    this->addChild(std::move(std::make_shared<Node>(shared_from_this(),
                                                          std::move(newPosition), this->layerNumber + 1)));
                }
                newPosition = std::make_shared<Board>(std::move(*position.get()));
            }
            else{
                break;
            }
        }
        for(int i = 9; i <= 63; i += 9){
            endSquare = square + i;
            if(endSquare > 63){
                break;
            }
            if(Move::openingPin(*newPosition.get(), square, endSquare)){
                break;
            }
            else if(Bishop_move::makeMove(*newPosition.get(), square, endSquare)){
                if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                    this->hasChildren = true;
                    if(!addingChildren){
                        return;
                    }
                    this->addChild(std::move(std::make_shared<Node>(shared_from_this(),
                                                          std::move(newPosition), this->layerNumber + 1)));
                }
                newPosition = std::make_shared<Board>(std::move(*position.get()));
            }
            else{
                break;
            }
        }
        for(int i = -9; i >= -63; i -= 9){
            endSquare = square + i;
            if(endSquare < 0){
                break;
            }
            if(Move::openingPin(*newPosition.get(), square, endSquare)){
                break;
            }
            else if(Bishop_move::makeMove(*newPosition.get(), square, endSquare)){
                if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                    this->hasChildren = true;
                    if(!addingChildren){
                        return;
                    }
                    this->addChild(std::move(std::make_shared<Node>(shared_from_this(),
                                                          std::move(newPosition), this->layerNumber + 1)));
                }
                newPosition = std::make_shared<Board>(std::move(*position.get()));
            }
            else{
                break;
            }
        }
        currentColorBishops &= ~((uint64_t) 1 << square);
    }

    auto currentColorKnights = position->currentColor() & position->knights;
    auto totalKnightNumber = popcount(currentColorKnights);
    for(int knightNumber = 0; knightNumber < totalKnightNumber; knightNumber++) {
        square = ctz(currentColorKnights);
        for(int delta: Knight_move::possibleKnightMoves){
            endSquare = square + delta;
            if(endSquare < 0 || endSquare > 63){
                continue;
            }
            if(Move::openingPin(*newPosition.get(), square, endSquare)){
                continue;
            }
            else if(Knight_move::makeMove(*newPosition.get(), square, endSquare)){
                if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                    this->hasChildren = true;
                    if(!addingChildren){
                        return;
                    }
                    this->addChild(std::move(std::make_shared<Node>(shared_from_this(),
                                                          std::move(newPosition), this->layerNumber + 1)));
                }
                newPosition = std::make_shared<Board>(std::move(*position.get()));
            }
        }
        currentColorKnights &= ~((uint64_t)1 << square);
    }

    auto currentColorPawns = position->currentColor() & position->pawns;
    auto totalPawnNumber = popcount(currentColorPawns);
    for(int pawnNumber = 0; pawnNumber < totalPawnNumber; pawnNumber++) {
        square = ctz(currentColorPawns);
        for(int i = 7; i <= 9; i++){
            for(int j = 0; j <= 1; j++){
                endSquare = square + (i + 8*j)*(-1+2*position->whiteOrder());
                if(endSquare > 63 || endSquare < 0){
                    break;
                }
                if(Move::openingPin(*newPosition.get(), square, endSquare)){
                    break;
                }
                else if (endSquare / 8 == 0 || endSquare / 8 == 7) {
                    std::vector<char> possiblePromotion = {'Q', 'R', 'B', 'N'};
                    for (char promotion : possiblePromotion) {
                        if (Pawn_move::makeMove(*newPosition.get(), square, endSquare, i != 8 , promotion)) {
                            if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                                this->hasChildren = true;
                                if(!addingChildren){
                                    return;
                                }
                                this->addChild(std::move(std::make_shared<Node>(shared_from_this(),
                                                                      std::move(newPosition), this->layerNumber + 1)));
                            }
                            newPosition = std::make_shared<Board>(std::move(*position.get()));
                        }
                        else {
                            break;
                        }
                    }
                }
                else if(Pawn_move::makeMove(*newPosition.get(), square, endSquare, i != 8)){
                    if (!newPosition->fieldIsDefended(newPosition->anotherColorKingPosition())) {
                        this->hasChildren = true;
                        if(!addingChildren){
                            return;
                        }
                        this->addChild(std::move(std::make_shared<Node>(shared_from_this(),
                                                              std::move(newPosition), this->layerNumber + 1)));
                    }
                    newPosition = std::make_shared<Board>(std::move(*position.get()));
                }

                else{
                    break;
                }
            }
        }
        currentColorPawns &= ~((uint64_t)1 << square);
    }
}

int Node::currentLayer(){
    return this->layerNumber;
}

void Node::addChildrenInQueue(std::queue<std::shared_ptr<Node>> &queue){
    for(const auto& child: this->children)
        queue.push(child);
}

void Node::showBoard() {
    this->position->showBoard();
}

int Node::childrenSize() {
    return this->children.size();
}

/*void Node::updateParentsPositionValue() {
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
}*/

void Node::updatePositionValue() {
    if (!this->evaluated){
        this->positionValue = std::optional<int>{ Evaluator::evaluatePosition(*this) };
        this->evaluated = true;
    }

    int val;
    int childValue;
    bool childrenHaveValue = true;
    if (this->position->whiteOrder()) {
        val = (this->childrenSize() == 0 && abs(this->positionValue.value()) != MAX_POS_VAL) ? 0 : -MAX_POS_VAL;
        for (const auto& child : this->children) {
            if(!child->positionValue.has_value()){
                childrenHaveValue = false;
                break;
            }
            childValue = child->positionValue.value() > MAX_POS_VAL - 100 ? 
                child->positionValue.value() - 1 : child->positionValue.value();
            val = val > childValue ? val : childValue;
        }
    }
    else {
        val = (this->childrenSize() == 0 && abs(this->positionValue.value()) != MAX_POS_VAL) ? 0 : MAX_POS_VAL;
        for (const auto& child : this->children) {
            if(!child->positionValue.has_value()){
                childrenHaveValue = false;
                break;
            }
            childValue = child->positionValue.value() < -MAX_POS_VAL + 100 ?
                child->positionValue.value() + 1 : child->positionValue.value();
            val = val < childValue ? val : childValue;
        }
    }
    if(childrenHaveValue){
        this->positionValue = std::optional<int>{ val };
    }
    // this->updateParentsPositionValue();
    if (this->layerNumber != 0) {
        this->parent.lock()->updatePositionValue();
    }
}

int Node::getPositionValue() {
    return this->positionValue.value();
}