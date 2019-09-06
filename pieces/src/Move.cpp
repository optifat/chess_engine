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

    if(!board->showCurrentColor()[initSquare]){
        std::cerr << "No piece with current color here\n";
        return false;
    }

    if(!board->isPinned(initSquare)){
        return false;
    }
    else if(!board->showAnotherColor()[endSquare]){
        board->showCurrentColor()[initSquare] = false;
        board->showCurrentColor()[endSquare] = true;
        if(board->fieldIsAttacked(kingPos)){
            board->showCurrentColor()[initSquare] = true;
            board->showCurrentColor()[endSquare] = false;
            return true;
        }
        else{
            board->showCurrentColor()[initSquare] = true;
            board->showCurrentColor()[endSquare] = false;
            return false;
        }
    }

    else{
        board->showCurrentColor()[initSquare] = false;
        board->showCurrentColor()[endSquare] = true;
        board->showAnotherColor()[endSquare] = false;
        if(board->fieldIsAttacked(kingPos)){
            board->showCurrentColor()[initSquare] = true;
            board->showCurrentColor()[endSquare] = false;
            board->showAnotherColor()[endSquare] = true;
            return true;
        }
        else{
            board->showCurrentColor()[initSquare] = true;
            board->showCurrentColor()[endSquare] = false;
            board->showAnotherColor()[endSquare] = true;
            return false;
        }
    }
}