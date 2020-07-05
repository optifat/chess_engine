#include <iostream>

#include "../include/Queen_move.h"

Queen_move::Queen_move(): Move(){};

void Queen_move::makeMove(Board *board, int initSquare, int endSquare, bool take) {

    // k variable shows "move direction".
    int k = 1;
    if(initSquare > endSquare)
        k = -1;

    if(initSquare/8 == endSquare/8 || initSquare%8 == endSquare%8){
        if(!take){
            if((initSquare - initSquare % 8) == (endSquare - endSquare % 8)){
                int i = initSquare + 1*k;
                for(; i*k <= endSquare*k; i+=1*k){
                    if(board->anotherColorCheck(i) || board->currentColorCheck(i)){
                        std::cerr << "Impossible move\n";
                        return;
                    }
                    else if(i == endSquare){
                        board->updateCurrentColor(initSquare, endSquare);
                        board->queens &= ~(1 << initSquare);
                        board->queens |= (1 << endSquare);
                        board->passTheMove();
                        return;
                    }
                }
            }
            else if(abs(initSquare - endSquare)  % 8 == 0){
                int i = initSquare + 8*k;
                for(; i*k <= endSquare*k; i+=8*k){
                    if(board->anotherColorCheck(i) || board->currentColorCheck(i)){
                        std::cerr << "Impossible move\n";
                        return;
                    }
                    else if(i == endSquare){
                        board->updateCurrentColor(initSquare, endSquare);
                        board->queens &= ~(1 << initSquare);
                        board->queens |= (1 << endSquare);
                        board->passTheMove();
                        return;
                    }
                }
            }
            else{
                std::cerr << "Impossible move\n";
                return;
            }
        }

        else{
            if((initSquare - initSquare % 8) == (endSquare - endSquare % 8)){
                int i = initSquare + 1*k;
                for(; i*k<=(endSquare-k)*k; i+=1*k){
                    if(board->anotherColorCheck(i) || board->currentColorCheck(i)){
                        std::cerr << "Impossible move\n";
                        return;
                    }
                    else if(i == endSquare-k){
                        if(board->anotherColorCheck(endSquare)){
                            board->updateCurrentColor(initSquare, endSquare);
                            board->updateAnotherColor(endSquare, -1);
                            board->queens &= ~(1 << initSquare);
                            board->queens |= (1 << endSquare);
                            board->pawns &= ~(1 << endSquare);
                            board->rooks &= ~(1 << endSquare);
                            board->knights &= ~(1 << endSquare);
                            board->bishops &= ~(1 << endSquare);
                            board->passTheMove();
                            return;
                        }
                        else{
                            std::cerr << "Impossible move\n";
                            return;
                        }
                    }
                }
            }
            else if(abs(initSquare - endSquare) % 8 == 0){
                int i = initSquare + 8*k;
                for(; i*k<=(endSquare-8)*k; i+=8*k){
                    if(board->anotherColorCheck(i) || board->currentColorCheck(i)){
                        std::cerr << "Impossible move\n";
                        return;
                    }
                    else if(i == endSquare-8*k){
                        if(board->anotherColorCheck(endSquare)){
                            board->updateCurrentColor(initSquare, endSquare);
                            board->updateAnotherColor(endSquare, -1);
                            board->queens &= ~(1 << initSquare);
                            board->queens |= (1 << endSquare);
                            board->pawns &= ~(1 << endSquare);
                            board->rooks &= ~(1 << endSquare);
                            board->knights &= ~(1 << endSquare);
                            board->bishops &= ~(1 << endSquare);
                            board->passTheMove();
                            return;
                        }
                        else{
                            std::cerr << "Impossible move\n";
                            return;
                        }
                    }
                }
            }
        }
    }
    else{


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
                            board->queens &= ~(1 << initSquare);
                            board->queens |= (1 << endSquare);
                            board->passTheMove();
                            return;
                        }
                    }
                }
                else if((endSquare - initSquare) % 9 == 0){
                    int i = initSquare + 9;
                    for(; i <= endSquare; i+=9){
                        if(board->anotherColorCheck(i) || board->currentColorCheck(i)){
                            std::cerr << "Impossible move\n";
                            return;
                        }
                        else if(i == endSquare){
                            board->updateCurrentColor(initSquare, endSquare);
                            board->queens &= ~(1 << initSquare);
                            board->queens |= (1 << endSquare);
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
                        if(board->anotherColorCheck(i) || board->currentColorCheck(i)){
                            std::cerr << "Impossible move\n";
                            return;
                        }
                        else if(i == endSquare){
                            board->updateCurrentColor(initSquare, endSquare);
                            board->queens &= ~(1 << initSquare);
                            board->queens |= (1 << endSquare);
                            board->passTheMove();
                            return;
                        }
                    }
                }
                else if((initSquare - endSquare) % 9 == 0){
                    int i = initSquare - 9;
                    for(; i >= endSquare; i-=9){
                        if(board->anotherColorCheck(i) || board->currentColorCheck(i)){
                            std::cerr << "Impossible move\n";
                            return;
                        }
                        else if(i == endSquare){
                            board->updateCurrentColor(initSquare, endSquare);
                            board->queens &= ~(1 << initSquare);
                            board->queens |= (1 << endSquare);
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
                        if(board->anotherColorCheck(i) || board->currentColorCheck(i)){
                            std::cerr << "Impossible move\n";
                            return;
                        }
                        else if(i == endSquare){
                            board->updateCurrentColor(initSquare, endSquare);
                            board->updateAnotherColor(endSquare, -1);
                            board->queens &= ~(1 << initSquare);
                            board->queens |= (1 << endSquare);
                            board->pawns &= ~(1 << endSquare);
                            board->rooks &= ~(1 << endSquare);
                            board->knights &= ~(1 << endSquare);
                            board->bishops &= ~(1 << endSquare);
                            board->passTheMove();
                            return;
                        }
                    }
                }
                else if((endSquare - initSquare) % 9 == 0){
                    int i = initSquare + 9;
                    for(; i <= endSquare; i+=9){
                        if(board->anotherColorCheck(i) || board->currentColorCheck(i)){
                            std::cerr << "Impossible move\n";
                            return;
                        }
                        else if(i == endSquare){
                            board->updateCurrentColor(initSquare, endSquare);
                            board->updateAnotherColor(endSquare, -1);
                            board->queens &= ~(1 << initSquare);
                            board->queens |= (1 << endSquare);
                            board->pawns &= ~(1 << endSquare);
                            board->rooks &= ~(1 << endSquare);
                            board->knights &= ~(1 << endSquare);
                            board->bishops &= ~(1 << endSquare);
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
                        if(board->anotherColorCheck(i) || board->currentColorCheck(i)){
                            std::cerr << "Impossible move\n";
                            return;
                        }
                        else if(i == endSquare){
                            board->updateCurrentColor(initSquare, endSquare);
                            board->updateAnotherColor(endSquare, -1);
                            board->queens &= ~(1 << initSquare);
                            board->queens |= (1 << endSquare);
                            board->pawns &= ~(1 << endSquare);
                            board->rooks &= ~(1 << endSquare);
                            board->knights &= ~(1 << endSquare);
                            board->bishops &= ~(1 << endSquare);
                            board->passTheMove();
                            return;
                        }
                    }
                }
                else if((initSquare - endSquare) % 9 == 0){
                    int i = initSquare - 9;
                    for(; i >= endSquare; i-=9){
                        if(board->anotherColorCheck(i) || board->currentColorCheck(i)){
                            std::cerr << "Impossible move\n";
                            return;
                        }
                        else if(i == endSquare){
                            board->updateCurrentColor(initSquare, endSquare);
                            board->updateAnotherColor(endSquare, -1);
                            board->queens &= ~(1 << initSquare);
                            board->queens |= (1 << endSquare);
                            board->pawns &= ~(1 << endSquare);
                            board->rooks &= ~(1 << endSquare);
                            board->knights &= ~(1 << endSquare);
                            board->bishops &= ~(1 << endSquare);
                            board->passTheMove();
                            return;
                        }
                    }
                }
                else std::cerr << "Impossible move\n";
            }
        }
    }
}