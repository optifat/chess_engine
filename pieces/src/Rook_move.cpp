#include <iostream>
#include <cmath>

#include "../include/Board.h"
#include "../include/Rook_move.h"
#include "../include/Move.h"

Rook_move::Rook_move(): Move(){};

void Rook_move::makeMove(Board *board, std::string move){
    if(move.length() != 5){
        std::cerr << "Wrong move input (length) \n";
        return;
    }else if(move[2] != '-' and move[2] != 'x'){
        std::cerr << "Wrong move input (not - or x)\n";
        return;
    } else if(move[0]>'h' or move[0]<'a' or move[3]>'h' or move[3]<'a'){
        std::cerr << "Wrong verticals, should be a-h \n";
        return;
    } else if(move[1]>'8' or move[1]<'1' or move[4]>'8' or move[4]<'1'){
        std::cerr << "Wrong horizontals, should be 1-8 \n";
        return;
    }

    int initSquare = move[0] - 'a' + 8*(move[1] - '1');
    int endSquare = move[3] - 'a' + 8*(move[4] - '1');

    if(!board->showRooks()[initSquare] or !board->showCurrentColor()[initSquare]){
        std::cerr << "No rook on " << move[0] << move[1]<<"\n";
        return;
    } else if(initSquare == endSquare){
        std::cerr << "Impossible move\n";
        return;
    }

    // k variable shows "move direction".
    int k = 1;
    if(initSquare > endSquare)
        k = -1;

    if(move[2] == '-'){
        if((initSquare - initSquare % 8) == (endSquare - endSquare % 8)){
            int i = initSquare + 1*k;
            for(i; i*k <= endSquare*k; i+=1*k){
                if(board->showAnotherColor()[i] or board->showCurrentColor()[i]){
                    std::cerr << "Impossible move\n";
                    return;
                }
                else if(i == endSquare){
                    board->showCurrentColor()[initSquare] = false;
                    board->showCurrentColor()[endSquare] = true;
                    board->showRooks()[initSquare] = false;
                    board->showRooks()[endSquare] = true;
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
                if(board->showAnotherColor()[i] or board->showCurrentColor()[i]){
                    std::cerr << "Impossible move\n";
                    return;
                }
                else if(i == endSquare){
                    board->showCurrentColor()[initSquare] = false;
                    board->showCurrentColor()[endSquare] = true;
                    board->showRooks()[initSquare] = false;
                    board->showRooks()[endSquare] = true;
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

    if(move[2] == 'x'){
        if((initSquare - initSquare % 8) == (endSquare - endSquare % 8)){
            int i = initSquare + 1*k;
            for(i; i*k<=(endSquare-k)*k; i+=1*k){
                if(board->showAnotherColor()[i] or board->showCurrentColor()[i]){
                    std::cerr << "Impossible move\n";
                    return;
                }
                else if(i == endSquare-k){
                    if(board->showAnotherColor()[endSquare]){
                        board->showPawns()[endSquare] = false;
                        board->showBishops()[endSquare] = false;
                        board->showKnights()[endSquare] = false;
                        board->showQueens()[endSquare] = false;
                        board->showCurrentColor()[initSquare] = false;
                        board->showAnotherColor()[endSquare] = false;
                        board->showCurrentColor()[endSquare] = true;
                        board->showRooks()[initSquare] = false;
                        board->showRooks()[endSquare] = true;
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
                if(board->showAnotherColor()[i] or board->showCurrentColor()[i]){
                    std::cerr << "Impossible move\n";
                    return;
                }
                else if(i == endSquare-8*k){
                    if(board->showAnotherColor()[endSquare]){
                        board->showPawns()[endSquare] = false;
                        board->showRooks()[endSquare] = false;
                        board->showBishops()[endSquare] = false;
                        board->showKnights()[endSquare] = false;
                        board->showQueens()[endSquare] = false;
                        board->showCurrentColor()[initSquare] = false;
                        board->showAnotherColor()[endSquare] = false;
                        board->showCurrentColor()[endSquare] = true;
                        board->showRooks()[initSquare] = false;
                        board->showRooks()[endSquare] = true;
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