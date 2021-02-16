#include <iostream>
#include <cmath>

#include "../include/Board.h"
#include "../include/Move.h"
#include "../include/Bishop_move.h"

// Bishop move has a "Ba1-h8" representation.
// Bishop capturing is similar to pawn capturing e.g. "Ba1xh8".

Bishop_move::Bishop_move(): Move(){};

bool Bishop_move::makeMove(Board *board, int initSquare, int endSquare){

    if(board->currentColorCheck(endSquare)){
        return false;
    }

    // k variable shows move direction: to the upper lines (k == 1) or lower ones (k == -1).
    int k = 1;
    if(initSquare > endSquare)
        k = -1;

    if (abs(endSquare / 8 - initSquare / 8) != abs(endSquare % 8 - initSquare % 8)) {
        return false;
    }

    int delta = 0;
    if(abs(endSquare - initSquare) % 9 == 0){
        delta = 9;
    }
    else if(abs(endSquare - initSquare) % 7 == 0){
        delta = 7;
    }

    for(int i = initSquare + delta*k; i != endSquare+delta*k; i+=delta*k){
        if(i == endSquare){
            board->updateCurrentColor(initSquare, endSquare);
            board->bishops &= ~((uint64_t)1 << initSquare);
            board->bishops |= ((uint64_t)1 << endSquare);
            board->updateAnotherColor(endSquare, -1);
            board->pawns &= ~((uint64_t)1 << endSquare);
            board->rooks &= ~((uint64_t)1 << endSquare);
            board->knights &= ~((uint64_t)1 << endSquare);
            board->queens &= ~((uint64_t)1 << endSquare);
            board->passTheMove();
            return true;
        }
        else if(board->currentColorCheck(i) || board->anotherColorCheck(i)){
            return false;
        }
    }
    return false;
}

