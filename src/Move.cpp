#include <iostream>
#include "../include/Move.h"

Move::Move() = default;

void Move::makeMove(Board *board, std::string move){};

bool Move::openingPin(Board *board, std::string move){

    int kingPos = -1;
    for(int i = 0; i <= 63; i++){
        if(board->showKings()[i] && board->showCurrentColor()[i]){
            kingPos = i;
            break;
        }
    }

    int initSquare = move[0] - 'a' + 8*(move[1] - '1');
    int endSquare = move[3] - 'a' + 8*(move[4] - '1');
    std::cout << board->fieldIsAttacked(kingPos, initSquare) << std::endl;
    return board->fieldIsAttacked(kingPos, initSquare);
}