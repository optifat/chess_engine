#include <iostream>
#include <cmath>

#include "../include/Board.h"
#include "../include/Rook_move.h"
#include "../include/Move.h"

Rook_move::Rook_move(): Move(){};

bool Rook_move::makeMove(Board *board, int initSquare, int endSquare, bool take){
    if(board->currentColorCheck(endSquare)){
        return false;
    }
    // k variable shows "move direction".
    int k = 1;
    if(initSquare > endSquare)
        k = -1;
    if(!take){
        if((initSquare/8) == (endSquare/8)){
            int i = initSquare + 1*k;
            for(; i != endSquare+k; i+=1*k){
                if(i == endSquare){
                    board->updateCurrentColor(initSquare, endSquare);
                    board->rooks &= ~((uint64_t)1 << initSquare);
                    board->rooks |= ((uint64_t)1 << endSquare);
                    board->passTheMove();
                    if(initSquare == 0 || board->whiteOrder()){
                        board->whiteLongCastle = false;
                    }else if(initSquare == 7 || board->whiteOrder()){
                        board->whiteShortCastle = false;
                    }else if(initSquare == 56 || !board->whiteOrder()){
                        board->blackLongCastle = false;
                    }else if(initSquare == 63 || !board->whiteOrder()){
                        board->blackShortCastle = false;
                    }
                    return true;
                }
                else if(board->anotherColorCheck(i) || board->currentColorCheck(i)){
                    std::cerr << "Impossible move: some other piece is blocking\n";
                    return false;
                }
            }
        }
        else if(abs(initSquare-endSquare)%8 == 0){
            int i = initSquare + 8*k;
            for(; i != endSquare+8*k; i+=8*k){
                if(i == endSquare){
                    board->updateCurrentColor(initSquare, endSquare);
                    board->rooks &= ~((uint64_t)1 << initSquare);
                    board->rooks |= ((uint64_t)1 << endSquare);
                    board->passTheMove();
                    if(initSquare == 0 || board->whiteOrder()){
                        board->whiteLongCastle = false;
                    }else if(initSquare == 7 || board->whiteOrder()){
                        board->whiteShortCastle = false;
                    }else if(initSquare == 56 || !board->whiteOrder()){
                        board->blackLongCastle = false;
                    }else if(initSquare == 63 || !board->whiteOrder()){
                        board->blackShortCastle = false;
                    }
                    return true;
                }
                else if(board->anotherColorCheck(i) || board->currentColorCheck(i)){
                    std::cerr << "Impossible move: some other piece is blocking\n";
                    return false;
                }
            }
        }
        else{
            std::cerr << "Impossible move\n";
            return false;
        }
    }
    else{
        if((initSquare/8) == (endSquare/8)){
            int i = initSquare + 1*k;
            for(; i != endSquare+k; i+=1*k){
                if(i == endSquare){
                    if(board->anotherColorCheck(endSquare)){
                        board->updateCurrentColor(initSquare, endSquare);
                        board->updateAnotherColor(endSquare, -1);
                        board->rooks &= ~((uint64_t)1 << initSquare);
                        board->rooks |= ((uint64_t)1 << endSquare);
                        board->pawns &= ~((uint64_t)1 << endSquare);
                        board->bishops &= ~((uint64_t)1 << endSquare);
                        board->knights &= ~((uint64_t)1 << endSquare);
                        board->queens &= ~((uint64_t)1 << endSquare);
                        board->passTheMove();
                        if(initSquare == 0 || board->whiteOrder()){
                            board->whiteLongCastle = false;
                        }else if(initSquare == 7 || board->whiteOrder()){
                            board->whiteShortCastle = false;
                        }else if(initSquare == 56 || !board->whiteOrder()){
                            board->blackLongCastle = false;
                        }else if(initSquare == 63 || !board->whiteOrder()){
                            board->blackShortCastle = false;
                        }
                        return true;
                    }

                    else{
                        std::cerr << "Impossible move\n";
                        return false;
                    }
                }
                else if(board->anotherColorCheck(i) || board->currentColorCheck(i)) {
                    std::cerr << "Impossible move: something is blocking\n";
                    return false;
                }
                else{
                    std::cerr << "Something went wrong\n";
                    return false;
                }
            }
        }
        else if(abs(initSquare-endSquare)%8 == 0){
            int i = initSquare + 8*k;
            for(; i!=endSquare+8*k; i+=8*k){
                if(i == endSquare){
                    if(board->anotherColorCheck(endSquare)){
                        board->updateCurrentColor(initSquare, endSquare);
                        board->updateAnotherColor(endSquare, -1);
                        board->rooks &= ~((uint64_t)1 << initSquare);
                        board->rooks |= ((uint64_t)1 << endSquare);
                        board->pawns &= ~((uint64_t)1 << endSquare);
                        board->bishops &= ~((uint64_t)1 << endSquare);
                        board->knights &= ~((uint64_t)1 << endSquare);
                        board->queens &= ~((uint64_t)1 << endSquare);
                        board->passTheMove();
                        if(initSquare == 0 || board->whiteOrder()){
                            board->whiteLongCastle = false;
                        }else if(initSquare == 7 || board->whiteOrder()){
                            board->whiteShortCastle = false;
                        }else if(initSquare == 56 || !board->whiteOrder()){
                            board->blackLongCastle = false;
                        }else if(initSquare == 63 || !board->whiteOrder()){
                            board->blackShortCastle = false;
                        }
                        return true;
                    }
                    else{
                        std::cerr << "Impossible move\n";
                        return false;
                    }
                }
                if(board->anotherColorCheck(i) || board->currentColorCheck(i)){
                    std::cerr << "Impossible move: some other piece is blocking\n";
                    return false;
                }
            }
        }
        else{
            std::cerr << "Impossible move\n";
            return false;
        }
    }
    return false;
}
