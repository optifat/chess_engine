#include <iostream>
#include <cmath>

#include "../include/Board.h"
#include "../include/Rook_move.h"
#include "../include/Move.h"

Rook_move::Rook_move(): Move(){};

void Rook_move::makeMove(Board *board, int initSquare, int endSquare, bool take){
    // k variable shows "move direction".
    int k = 1;
    if(initSquare > endSquare)
        k = -1;

    if(!take){
        if((initSquare - initSquare % 8) == (endSquare - endSquare % 8)){
            int i = initSquare + 1*k;
            for(; i*k <= endSquare*k; i+=1*k){
                if(board->anotherColorCheck(i) or board->currentColorCheck(i)){
                    std::cerr << "Impossible move\n";
                    return;
                }
                else if(i == endSquare){
                    board->updateCurrentColor(initSquare, endSquare);
                    board->rooks &= ~(1 << initSquare);
                    board->rooks |= (1 << endSquare);
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
                    return;
                }
            }
        }
        else if(abs(initSquare - endSquare)  % 8 == 0){
            int i = initSquare + 8*k;
            for(i; i*k <= endSquare*k; i+=8*k){
                if(board->anotherColorCheck(i) || board->currentColorCheck(i)){
                    std::cerr << "Impossible move\n";
                    return;
                }
                else if(i == endSquare){
                    board->updateCurrentColor(initSquare, endSquare);
                    board->rooks &= ~(1 << initSquare);
                    board->rooks |= (1 << endSquare);
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
                if(board->anotherColorCheck(i) or board->currentColorCheck(i)){
                    std::cerr << "Impossible move\n";
                    return;
                }
                else if(i == endSquare-k){
                    if(board->anotherColorCheck(endSquare)){
                        board->updateCurrentColor(initSquare, endSquare);
                        board->updateAnotherColor(endSquare, -1);
                        board->rooks &= ~(1 << initSquare);
                        board->rooks |= (1 << endSquare);
                        board->pawns &= ~(1 << endSquare);
                        board->bishops &= ~(1 << endSquare);
                        board->knights &= ~(1 << endSquare);
                        board->queens &= ~(1 << endSquare);
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
            for(i; i*k<=(endSquare-8)*k; i+=8*k){
                if(board->anotherColorCheck(i) or board->currentColorCheck(i)){
                    std::cerr << "Impossible move\n";
                    return;
                }
                else if(i == endSquare-8*k){
                    if(board->anotherColorCheck(endSquare)){
                        board->updateCurrentColor(initSquare, endSquare);
                        board->updateAnotherColor(endSquare, -1);
                        board->rooks &= ~(1 << initSquare);
                        board->rooks |= (1 << endSquare);
                        board->pawns &= ~(1 << endSquare);
                        board->bishops &= ~(1 << endSquare);
                        board->knights &= ~(1 << endSquare);
                        board->queens &= ~(1 << endSquare);
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
                        return;
                    }
                    else{
                        std::cerr << "Impossible move\n";
                        return;
                    }
                }
            }
        }
        else{
            std::cerr << "Impossible move\n";
            return;
        }
    }
}
