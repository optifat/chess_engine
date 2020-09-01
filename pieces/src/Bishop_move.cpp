#include <iostream>
#include <cmath>

#include "../include/Board.h"
#include "../include/Move.h"
#include "../include/Bishop_move.h"

// Bishop move has a "Ba1-h8" representation.
// Bishop capturing is similar to pawn capturing e.g. "Ba1xh8".

Bishop_move::Bishop_move(): Move(){};

bool Bishop_move::makeMove(Board *board, int initSquare, int endSquare, bool take){

    if(board->currentColorCheck(endSquare)){
        return false;
    }

    // k variable shows move direction: to the upper lines (k == 1) or lower ones (k == -1).
    int k = 1;
    if(initSquare > endSquare)
        k = -1;

    if(!take){
        if(abs(endSquare - initSquare) % 7 == 0){
            int i = initSquare + 7*k;
            for(; i != endSquare+7*k; i+=7*k){
                if(board->anotherColorCheck(i) || board->currentColorCheck(i)){
                    std::cerr << "Impossible move\n";
                    return false;
                }
                else if(i == endSquare){
                    board->updateCurrentColor(initSquare, endSquare);
                    board->bishops &= ~((uint64_t)1 << initSquare);
                    board->bishops |= ((uint64_t)1 << endSquare);
                    board->passTheMove();
                    return true;
                }
            }
        }
        else if(abs(endSquare - initSquare) % 9 == 0){
            int i = initSquare + 9*k;
            for(; i != endSquare+9*k; i+=9*k){
                if(board->anotherColorCheck(i) || board->currentColorCheck(i)){
                    std::cerr << "Impossible move\n";
                    return false;
                }
                else if(i == endSquare){
                    board->updateCurrentColor(initSquare, endSquare);
                    board->bishops &= ~((uint64_t)1 << initSquare);
                    board->bishops |= ((uint64_t)1 << endSquare);
                    board->passTheMove();
                    return true;
                }
            }
        }
        else {
            std::cerr << "Impossible move\n";
            return false;
        }
    }
    else{
        if(abs(endSquare - initSquare) % 7 == 0){
            int i = initSquare + 7*k;
            for(; i != endSquare+7*k; i+=7*k){
                std::cout << i << std::endl;
                if(i == endSquare){
                    board->updateCurrentColor(initSquare, endSquare);
                    board->updateAnotherColor(endSquare, -1);
                    board->bishops &= ~((uint64_t)1 << initSquare);
                    board->bishops |= ((uint64_t)1 << endSquare);
                    board->pawns &= ~((uint64_t)1 << endSquare);
                    board->rooks &= ~((uint64_t)1 << endSquare);
                    board->knights &= ~((uint64_t)1 << endSquare);
                    board->queens &= ~((uint64_t)1 << endSquare);
                    board->passTheMove();
                    return true;
                }
                else if(board->currentColorCheck(i)){
                    std::cerr << "Impossible move\n";
                    return false;
                }
            }
        }
        else if(abs(endSquare - initSquare) % 9 == 0){
            int i = initSquare + 9*k;
            for(; i != endSquare + 9*k; i+=9*k){
                if(i == endSquare){
                    board->updateCurrentColor(initSquare, endSquare);
                    board->updateAnotherColor(endSquare, -1);
                    board->bishops &= ~((uint64_t)1 << initSquare);
                    board->bishops |= ((uint64_t)1 << endSquare);
                    board->pawns &= ~((uint64_t)1 << endSquare);
                    board->rooks &= ~((uint64_t)1 << endSquare);
                    board->knights &= ~((uint64_t)1 << endSquare);
                    board->queens &= ~((uint64_t)1 << endSquare);
                    board->passTheMove();
                    return true;
                }
                else if(board->anotherColorCheck(i) || board->currentColorCheck(i)){
                    std::cerr << "Impossible move\n";
                    return false;
                }
            }
        }
        else {
            std::cerr << "Impossible move\n";
            return false;
        }
    }
    return false;
}

