#include <iostream>

#include "../include/King_move.h"

King_move::King_move(): Move(){};

void King_move::makeMove(Board *board, int initSquare, int endSquare, bool take) {

    if(abs(initSquare/8-endSquare/8) > 1 || abs(initSquare%8-endSquare%8) > 1){
        std::cerr << "Impossible move\n";
        return;
    }

    if(!take){
        board->updateCurrentColor(initSquare, endSquare);
        board->kings &= ~(1 << initSquare);
        board->kings |= (1 << endSquare);
        if(board->whiteToMove){
            board->whiteLongCastle = false;
            board->whiteShortCastle = false;
        }
        else{
            board->blackLongCastle = false;
            board->blackShortCastle = false;
        }
        board->passTheMove();
        return;
    }
    else{
        board->updateCurrentColor(initSquare, endSquare);
        board->updateAnotherColor(endSquare, -1);
        board->kings &= ~((uint64_t)1 << initSquare);
        board->kings |= ((uint64_t)1 << endSquare);
        board->pawns &= ~((uint64_t)1 << endSquare);
        board->bishops &= ~((uint64_t)1 << endSquare);
        board->rooks &= ~((uint64_t)1 << endSquare);
        board->knights &= ~((uint64_t)1 << endSquare);
        board->queens &= ~((uint64_t)1 << endSquare);
        if(board->whiteToMove){
            board->whiteLongCastle = false;
            board->whiteShortCastle = false;
        }
        else{
            board->blackLongCastle = false;
            board->blackShortCastle = false;
        }
        board->passTheMove();
        return;
    }
}
