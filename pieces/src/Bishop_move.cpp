#include <iostream>
#include <cmath>

#include "../include/Board.h"
#include "../include/Move.h"
#include "../include/Bishop_move.h"

// Bishop move has a "Ba1-h8" representation.
// Bishop capturing is similar to pawn capturing e.g. "Ba1xh8".

Bishop_move::Bishop_move(): Move(){};

void Bishop_move::makeMove(Board *board, int initSquare, int endSquare, bool take){

    // k variable shows move direction: to the upper lines (k == 1) or lower ones (k == -1).
    int k = 1;
    if(initSquare > endSquare)
        k = -1;

    if(!take){
        if(k == 1){
            if((endSquare - initSquare) % 7 == 0){
                int i = initSquare + 7;
                for(; i <= endSquare; i+=7){
                    if(board->anotherColorCheck(i) || board->currentColorCheck(i)){
                        std::cerr << "Impossible move\n";
                        return;
                    }
                    else if(i == endSquare){
                        board->updateCurrentColor(initSquare, endSquare);
                        board->bishops &= ~(1 << initSquare);
                        board->bishops |= (1 << endSquare);
                        board->passTheMove();
                        return;
                    }
                }
            }
            else if((endSquare - initSquare) % 9 == 0){
                int i = initSquare + 9;
                for(; i <= endSquare; i+=9){
                    if(board->anotherColorCheck(i) or board->currentColorCheck(i)){
                        std::cerr << "Impossible move\n";
                        return;
                    }
                    else if(i == endSquare){
                        board->updateCurrentColor(initSquare, endSquare);
                        board->bishops &= ~(1 << initSquare);
                        board->bishops |= (1 << endSquare);
                        board->passTheMove();
                        return;
                    }
                }
            }
            else std::cerr << "Impossible move\n";
        }
        else {
            if((initSquare - endSquare) % 7 == 0){
                int i = initSquare - 7;
                for(; i >= endSquare; i-=7){
                    if(board->anotherColorCheck(i) or board->currentColorCheck(i)){
                        std::cerr << "Impossible move\n";
                        return;
                    }
                    else if(i == endSquare){
                        board->updateCurrentColor(initSquare, endSquare);
                        board->bishops &= ~(1 << initSquare);
                        board->bishops |= (1 << endSquare);
                        board->passTheMove();
                        return;
                    }
                }
            }
            else if((initSquare - endSquare) % 9 == 0){
                int i = initSquare - 9;
                for(; i >= endSquare; i-=9){
                    if(board->anotherColorCheck(i) or board->currentColorCheck(i)){
                        std::cerr << "Impossible move\n";
                        return;
                    }
                    else if(i == endSquare){
                        board->updateCurrentColor(initSquare, endSquare);
                        board->bishops &= ~(1 << initSquare);
                        board->bishops |= (1 << endSquare);
                        board->passTheMove();
                        return;
                    }
                }
            }
            else std::cerr << "Impossible move\n";
        }
    }
    else{
        if(k == 1){
            if((endSquare - initSquare) % 7 == 0){
                int i = initSquare + 7;
                for(; i <= endSquare; i+=7){
                    if(board->currentColorCheck(i)){
                        std::cerr << "Impossible move1\n";
                        return;
                    }
                    else if(i == endSquare){
                        board->updateCurrentColor(initSquare, endSquare);
                        board->updateAnotherColor(endSquare, -1);
                        board->bishops &= ~(1 << initSquare);
                        board->bishops |= (1 << endSquare);
                        board->pawns &= ~(1 << endSquare);
                        board->rooks &= ~(1 << endSquare);
                        board->knights &= ~(1 << endSquare);
                        board->queens &= ~(1 << endSquare);
                        board->passTheMove();
                        return;
                    }
                }
            }
            else if((endSquare - initSquare) % 9 == 0){
                int i = initSquare + 9;
                for(; i <= endSquare; i+=9){
                    if(board->anotherColorCheck(i) or board->currentColorCheck(i)){
                        std::cerr << "Impossible move2\n";
                        return;
                    }
                    else if(i == endSquare){
                        board->updateCurrentColor(initSquare, endSquare);
                        board->updateAnotherColor(endSquare, -1);
                        board->bishops &= ~(1 << initSquare);
                        board->bishops |= (1 << endSquare);
                        board->pawns &= ~(1 << endSquare);
                        board->rooks &= ~(1 << endSquare);
                        board->knights &= ~(1 << endSquare);
                        board->queens &= ~(1 << endSquare);
                        board->passTheMove();
                        return;
                    }
                }
            }
            else std::cerr << "Impossible move3\n";
        }
        else {
            if((initSquare - endSquare) % 7 == 0){
                int i = initSquare - 7;
                for(; i >= endSquare; i-=7){
                    if(board->anotherColorCheck(i) or board->currentColorCheck(i)){
                        std::cerr << "Impossible move\n";
                        return;
                    }
                    else if(i == endSquare){
                        board->bishops &= ~(1 << initSquare);
                        board->bishops |= (1 << endSquare);
                        board->bishops -= powl(2, initSquare);
                        board->bishops += powl(2, endSquare);
                        board->pawns &= ~(1 << endSquare);
                        board->rooks &= ~(1 << endSquare);
                        board->knights &= ~(1 << endSquare);
                        board->queens &= ~(1 << endSquare);
                        board->passTheMove();
                        return;
                    }
                }
            }
            else if((initSquare - endSquare) % 9 == 0){
                int i = initSquare - 9;
                for(; i >= endSquare; i-=9){
                    if(board->anotherColorCheck(i) or board->currentColorCheck(i)){
                        std::cerr << "Impossible move\n";
                        return;
                    }
                    else if(i == endSquare){
                        board->updateCurrentColor(initSquare, endSquare);
                        board->updateAnotherColor(endSquare, -1);
                        board->bishops &= ~(1 << initSquare);
                        board->bishops |= (1 << endSquare);
                        board->pawns &= ~(1 << endSquare);
                        board->rooks &= ~(1 << endSquare);
                        board->knights &= ~(1 << endSquare);
                        board->queens &= ~(1 << endSquare);
                        board->passTheMove();
                        return;
                    }
                }
            }
            else std::cerr << "Impossible move\n";
        }
    }
}

