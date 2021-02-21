#include <iostream>

#include "../include/King_move.h"

King_move::King_move(): Move(){};

bool King_move::makeMove(Board& board, int initSquare, int endSquare) {
    if(board.currentColorCheck(endSquare)){
        return false;
    }

    if(abs(initSquare/8-endSquare/8) > 1 || abs(initSquare%8-endSquare%8) > 1){
        return false;
    }

    if(board.fieldIsAttacked(endSquare)){
        return false;
    }

    board.updateCurrentColor(initSquare, endSquare);
    board.kings &= ~((uint64_t)1 << initSquare);
    board.kings |= ((uint64_t)1 << endSquare);
    board.updateAnotherColor(endSquare, -1);
    board.pawns &= ~((uint64_t)1 << endSquare);
    board.bishops &= ~((uint64_t)1 << endSquare);
    board.rooks &= ~((uint64_t)1 << endSquare);
    board.knights &= ~((uint64_t)1 << endSquare);
    board.queens &= ~((uint64_t)1 << endSquare);
    if(board.whiteToMove){
        board.whiteLongCastle = false;
        board.whiteShortCastle = false;
    }
    else{
        board.blackLongCastle = false;
        board.blackShortCastle = false;
    }
    board.passTheMove();
    return true;
}
