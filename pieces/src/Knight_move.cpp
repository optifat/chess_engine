#include <iostream>
#include <cmath>
#include <set>

#include "../include/Board.h"
#include "../include/Move.h"
#include "../include/Knight_move.h"


Knight_move::Knight_move(): Move(){};

bool Knight_move::makeMove(Board *board, int initSquare, int endSquare, bool take){

    std::set<int> possibleMoves = {-17, -15, -10, -6, 6, 10, 15, 17};

    if(possibleMoves.find(initSquare - endSquare) == possibleMoves.end()){
        std::cerr << "Impossible move\n";
        return false;
    } else if(abs(initSquare/8-endSquare/8)+abs(initSquare%8-endSquare%8) != 3){
        std::cerr << "Impossible move\n";
        return false;
    }

    if(!take){
        board->updateCurrentColor(initSquare, endSquare);
        board->knights &= ~((uint64_t)1 << initSquare);
        board->knights |= ((uint64_t)1 << endSquare);
        board->passTheMove();
        return true;
    }
    else{
        board->updateCurrentColor(initSquare, endSquare);
        board->updateAnotherColor(endSquare, -1);
        board->knights &= ~((uint64_t)1 << initSquare);
        board->knights |= ((uint64_t)1 << endSquare);
        board->pawns &= ~((uint64_t)1 << endSquare);
        board->rooks &= ~((uint64_t)1 << endSquare);
        board->bishops &= ~((uint64_t)1 << endSquare);
        board->queens &= ~((uint64_t)1 << endSquare);
        board->passTheMove();
        return true;
    }
}

