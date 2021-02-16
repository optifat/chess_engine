#include <iostream>

#include "../include/Queen_move.h"

Queen_move::Queen_move(): Move(){};

bool Queen_move::makeMove(Board *board, int initSquare, int endSquare) {

    if(board->currentColorCheck(endSquare)){
        return false;
    }

    // k variable shows "move direction".
    int k = 1;
    if(initSquare > endSquare)
        k = -1;

    int delta = 0;
    if(initSquare/8 == endSquare/8) {
        delta = 1;
    }
    else if(abs(initSquare - endSquare) % 8 == 0){
        delta = 8;
    }
    else if(abs(endSquare - initSquare) % 9 == 0 && abs(endSquare / 8 - initSquare / 8) == abs(endSquare % 8 - initSquare % 8)){
        delta = 9;
    }
    else if(abs(endSquare - initSquare) % 7 == 0 && abs(endSquare / 8 - initSquare / 8) == abs(endSquare % 8 - initSquare % 8)){
        delta = 7;
    }
    else{
        return false;
    }

    for(int i = initSquare + delta*k; i != endSquare+delta*k; i+=delta*k){
        if(i == endSquare){
            board->updateCurrentColor(initSquare, endSquare);
            board->queens &= ~((uint64_t)1 << initSquare);
            board->queens |= ((uint64_t)1 << endSquare);
            board->updateAnotherColor(endSquare, -1);
            board->pawns &= ~((uint64_t)1 << endSquare);
            board->rooks &= ~((uint64_t)1 << endSquare);
            board->knights &= ~((uint64_t)1 << endSquare);
            board->bishops &= ~((uint64_t)1 << endSquare);
            board->passTheMove();
            return true;
        }
        else if(board->anotherColorCheck(i) || board->currentColorCheck(i)){
            return false;
        }
    }
    return false;
}