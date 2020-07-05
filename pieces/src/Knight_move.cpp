#include <iostream>
#include <cmath>
#include <set>

#include "../include/Board.h"
#include "../include/Move.h"
#include "../include/Knight_move.h"


Knight_move::Knight_move(): Move(){};

void Knight_move::makeMove(Board *board, int initSquare, int endSquare, bool take){
    /*
    std::set<int> possibleMoves = {-17, -15, -10, -6, 6, 10, 15, 17};

    if(!board->knights[initSquare] or !board->showCurrentColor()[initSquare]){
        std::cerr << "No knight on " << move[0] << move[1]<<"\n";
        return;
    } else if(possibleMoves.find(initSquare - endSquare) == possibleMoves.end()){
        std::cerr << "Impossible move\n";
        return;
    } else if(abs(initSquare/8-endSquare/8)+abs(initSquare%8-endSquare%8) != 3){  //need to think how to deal with impossible moves like Na8-g8
        std::cerr << "Impossible move\n";
        return;
    }
    */
    //std::cout << endSquare/8 - initSquare/8 << ' ' << (initSquare-endSquare+1)/8 << std::endl;

    if(!take){
        board->updateCurrentColor(initSquare, endSquare);
        board->bishops &= ~(1 << initSquare);
        board->bishops |= (1 << endSquare);
        board->passTheMove();
    }
    else{
        board->updateCurrentColor(initSquare, endSquare);
        board->updateAnotherColor(endSquare, -1);
        board->knights &= ~(1 << initSquare);
        board->knights |= (1 << endSquare);
        board->pawns &= ~(1 << endSquare);
        board->rooks &= ~(1 << endSquare);
        board->bishops &= ~(1 << endSquare);
        board->queens &= ~(1 << endSquare);
        board->passTheMove();
    }
}

