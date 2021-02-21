#include <iostream>
#include <cmath>
#include <set>

#include "../include/Board.h"
#include "../include/Move.h"
#include "../include/Knight_move.h"


Knight_move::Knight_move(): Move(){};

bool Knight_move::makeMove(Board& board, int initSquare, int endSquare){
    if(board.currentColorCheck(endSquare)){
        return false;
    }

    std::set<int> possibleMoves = {-17, -15, -10, -6, 6, 10, 15, 17};

    if(possibleMoves.find(initSquare - endSquare) == possibleMoves.end()){
        return false;
    } else if(abs(initSquare/8-endSquare/8)+abs(initSquare%8-endSquare%8) != 3){
        return false;
    }

    board.updateCurrentColor(initSquare, endSquare);
    board.knights &= ~((uint64_t)1 << initSquare);
    board.knights |= ((uint64_t)1 << endSquare);
    board.updateAnotherColor(endSquare, -1);
    board.pawns &= ~((uint64_t)1 << endSquare);
    board.rooks &= ~((uint64_t)1 << endSquare);
    board.bishops &= ~((uint64_t)1 << endSquare);
    board.queens &= ~((uint64_t)1 << endSquare);
    board.passTheMove();
    return true;
}

