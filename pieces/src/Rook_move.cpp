#include <iostream>
#include <cmath>

#include "../include/Board.h"
#include "../include/Rook_move.h"
#include "../include/Move.h"

Rook_move::Rook_move(): Move(){};

bool Rook_move::makeMove(Board& board, int initSquare, int endSquare){
    if(board.currentColorCheck(endSquare)){
        return false;
    }
    // k variable shows "move direction".
    int k = 1;
    if(initSquare > endSquare)
        k = -1;

    int delta = 0;
    if(initSquare/8 == endSquare/8){
        delta = 1;
    }
    else if(abs(initSquare-endSquare)%8 == 0){
        delta = 8;
    }

    for(int i = initSquare + delta*k; i != endSquare+k; i+=delta*k){
        if(i == endSquare){
            board.updateCurrentColor(initSquare, endSquare);
            board.rooks &= ~((uint64_t)1 << initSquare);
            board.rooks |= ((uint64_t)1 << endSquare);
            board.updateAnotherColor(endSquare, -1);
            board.pawns &= ~((uint64_t)1 << endSquare);
            board.bishops &= ~((uint64_t)1 << endSquare);
            board.knights &= ~((uint64_t)1 << endSquare);
            board.queens &= ~((uint64_t)1 << endSquare);

            board.whiteLongCastle = (board.whiteLongCastle && initSquare != 0);
            board.whiteShortCastle = (board.whiteShortCastle && initSquare != 7);
            board.blackLongCastle = (board.blackLongCastle && initSquare != 56);
            board.blackShortCastle = (board.blackShortCastle && initSquare != 63);

            board.passTheMove();
            return true;
        }
        else if(board.anotherColorCheck(i) || board.currentColorCheck(i)) {
            return false;
        }
    }
    return false;
}
