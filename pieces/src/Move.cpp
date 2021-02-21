#include <iostream>
#include "../include/Move.h"

Move::Move() = default;

bool Move::openingPin(Board board, int initSquare, int endSquare){

    int kingPos = board.currentColorKingPosition();

    if(!board.currentColorCheck(initSquare)){
        return false;
    }

    if(!board.isPinned(initSquare)){
        return false;
    }

    board.updateCurrentColor(initSquare, endSquare);
    board.updateAnotherColor(endSquare, -1);
    return board.fieldIsAttacked(kingPos);
}