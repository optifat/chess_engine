#include <iostream>

#include "../include/Queen_move.h"

Queen_move::Queen_move(): Move(){};

bool Queen_move::makeMove(Board *board, int initSquare, int endSquare, bool take) {

    // k variable shows "move direction".
    int k = 1;
    if(initSquare > endSquare)
        k = -1;

    if(initSquare/8 == endSquare/8 || initSquare%8 == endSquare%8){
        if(!take){
            if((initSquare - initSquare % 8) == (endSquare - endSquare % 8)){
                int i = initSquare + k;
                for(; i != endSquare+k; i+=k){
                    if(board->anotherColorCheck(i) || board->currentColorCheck(i)){
                        std::cerr << "Impossible move\n";
                        return false;
                    }
                    else if(i == endSquare){
                        board->updateCurrentColor(initSquare, endSquare);
                        board->queens &= ~((uint64_t)1 << initSquare);
                        board->queens |= ((uint64_t)1 << endSquare);
                        board->passTheMove();
                        return true;
                    }
                }
            }
            else if(abs(initSquare - endSquare)%8 == 0){
                int i = initSquare + 8*k;
                for(; i != endSquare+8*k; i+=8*k){
                    if(board->anotherColorCheck(i) || board->currentColorCheck(i)){
                        std::cerr << "Impossible move\n";
                        return false;
                    }
                    else if(i == endSquare){
                        board->updateCurrentColor(initSquare, endSquare);
                        board->queens &= ~((uint64_t)1 << initSquare);
                        board->queens |= ((uint64_t)1 << endSquare);
                        board->passTheMove();
                        return true;
                    }
                }
            }
            else{
                std::cerr << "Impossible move\n";
                return false;
            }
        }

        else{
            if((initSquare - initSquare % 8) == (endSquare - endSquare % 8)){
                int i = initSquare + k;
                for(; i!=endSquare+1; i+=k){
                    if(i == endSquare){
                        if(board->anotherColorCheck(endSquare)){
                            board->updateCurrentColor(initSquare, endSquare);
                            board->updateAnotherColor(endSquare, -1);
                            board->queens &= ~((uint64_t)1 << initSquare);
                            board->queens |= ((uint64_t)1 << endSquare);
                            board->pawns &= ~((uint64_t)1 << endSquare);
                            board->rooks &= ~((uint64_t)1 << endSquare);
                            board->knights &= ~((uint64_t)1 << endSquare);
                            board->bishops &= ~((uint64_t)1 << endSquare);
                            board->passTheMove();
                            return true;
                        }
                        else{
                            std::cerr << "Impossible move\n";
                            return false;
                        }
                    }
                    else if(board->anotherColorCheck(i) || board->currentColorCheck(i)) {
                        std::cerr << "Impossible move\n";
                        return false;
                    }
                }
            }
            else if(abs(initSquare - endSquare) % 8 == 0){
                int i = initSquare + 8*k;
                for(; i != endSquare+8*k; i+=8*k){
                    if(i == endSquare-8*k){
                        if(board->anotherColorCheck(endSquare)){
                            board->updateCurrentColor(initSquare, endSquare);
                            board->updateAnotherColor(endSquare, -1);
                            board->queens &= ~((uint64_t)1 << initSquare);
                            board->queens |= ((uint64_t)1 << endSquare);
                            board->pawns &= ~((uint64_t)1 << endSquare);
                            board->rooks &= ~((uint64_t)1 << endSquare);
                            board->knights &= ~((uint64_t)1 << endSquare);
                            board->bishops &= ~((uint64_t)1 << endSquare);
                            board->passTheMove();
                            return true;
                        }
                        else{
                            std::cerr << "Impossible move\n";
                            return false;
                        }
                    }
                    else if(board->anotherColorCheck(i) || board->currentColorCheck(i)) {
                        std::cerr << "Impossible move\n";
                        return false;
                    }
                }
            }
        }
    }
    else{
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
                        board->queens &= ~((uint64_t)1 << initSquare);
                        board->queens |= ((uint64_t)1 << endSquare);
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
                        board->queens &= ~((uint64_t)1 << initSquare);
                        board->queens |= ((uint64_t)1 << endSquare);
                        board->passTheMove();
                        return true;
                    }
                }
            }
            else{
                std::cerr << "Impossible move\n";
                return false;
            }
        }
        else{
            if(abs(endSquare - initSquare) % 7 == 0){
                int i = initSquare + 7*k;
                for(; i != endSquare+7*k; i+=7*k){
                    if(i == endSquare){
                        board->updateCurrentColor(initSquare, endSquare);
                        board->updateAnotherColor(endSquare, -1);
                        board->queens &= ~((uint64_t)1 << initSquare);
                        board->queens |= ((uint64_t)1 << endSquare);
                        board->pawns &= ~((uint64_t)1 << endSquare);
                        board->rooks &= ~((uint64_t)1 << endSquare);
                        board->knights &= ~((uint64_t)1 << endSquare);
                        board->bishops &= ~((uint64_t)1 << endSquare);
                        board->passTheMove();
                        return true;
                    }
                    else if(board->anotherColorCheck(i) || board->currentColorCheck(i)){
                        std::cerr << "Impossible move\n";
                        return false;
                    }
                }
            }
            else if(abs(endSquare - initSquare) % 9 == 0){
                int i = initSquare + 9*k;
                for(; i != endSquare+9*k; i+=9*k){
                    if(i == endSquare){
                        board->updateCurrentColor(initSquare, endSquare);
                        board->updateAnotherColor(endSquare, -1);
                        board->queens &= ~((uint64_t)1 << initSquare);
                        board->queens |= ((uint64_t)1 << endSquare);
                        board->pawns &= ~((uint64_t)1 << endSquare);
                        board->rooks &= ~((uint64_t)1 << endSquare);
                        board->knights &= ~((uint64_t)1 << endSquare);
                        board->bishops &= ~((uint64_t)1 << endSquare);
                        board->passTheMove();
                        return true;
                    }
                    else if(board->anotherColorCheck(i) || board->currentColorCheck(i)){
                        std::cerr << "Impossible move\n";
                        return false;
                    }
                }
            }
            else{
                std::cerr << "Impossible move\n";
                return false;
            }
        }
    }
    return false;
}