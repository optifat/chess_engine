#include <iostream>
#include "../include/Move.h"

Move::Move() = default;

//void Move::makeMove(Board *board, int initSquare, int endSquare, bool take){};

bool Move::openingPin(Board * position, int initSquare, int endSquare){

    auto board = *position;

    int kingPos = -1;
    for(int i = 0; i <= 63; i++){
        if(board.kingCheck(i) && board.currentColorCheck(i)){
            kingPos = i;
            break;
        }
    }

    if(!board.currentColorCheck(initSquare)){
        std::cerr << "No piece with current color here\n";
        return false;
    }

    if(!board.isPinned(initSquare)){
        return false;
    }
    else if(!board.anotherColorCheck(endSquare)){
        board.updateCurrentColor(initSquare, endSquare);
        //board.showCurrentColor()[initSquare] = false;
        //board.showCurrentColor()[endSquare] = true;
        if(board.fieldIsAttacked(kingPos)){
            board.updateCurrentColor(endSquare, initSquare);
            //board.showCurrentColor()[initSquare] = true;
            //board.showCurrentColor()[endSquare] = false;
            return true;
        }
        else{
            board.updateCurrentColor(endSquare, initSquare);
            //board.showCurrentColor()[initSquare] = true;
            //board.showCurrentColor()[endSquare] = false;
            return false;
        }
    }

    else{
        board.updateCurrentColor(initSquare, endSquare);
        board.updateAnotherColor(endSquare, -1);
        if(board.fieldIsAttacked(kingPos)){
            board.updateCurrentColor(endSquare, initSquare);
            board.updateAnotherColor(-1, endSquare);
            return true;
        }
        else{
            board.updateCurrentColor(endSquare, initSquare);
            board.updateAnotherColor(-1, endSquare);
            return false;
        }
    }
}