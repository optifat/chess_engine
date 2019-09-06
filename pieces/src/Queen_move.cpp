#include <iostream>

#include "../include/Queen_move.h"

Queen_move::Queen_move(): Move(){};

void Queen_move::makeMove(Board *board, std::string move) {

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

    if(!board->showQueens()[initSquare] or !board->showCurrentColor()[initSquare]){
        std::cerr << "No queen on " << move[0] << move[1]<<"\n";
        return;
    } else if(initSquare == endSquare){
        std::cerr << "Impossible move\n";
        return;
    }

    // k variable shows "move direction".
    int k = 1;
    if(initSquare > endSquare)
        k = -1;

    if(move[0] == move[3] || move[1] == move[4]){
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
                        board->showQueens()[initSquare] = false;
                        board->showQueens()[endSquare] = true;
                        board->passTheMove();
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
                        board->showQueens()[initSquare] = false;
                        board->showQueens()[endSquare] = true;
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
                            board->showRooks()[endSquare] = false;
                            board->showCurrentColor()[initSquare] = false;
                            board->showAnotherColor()[endSquare] = false;
                            board->showCurrentColor()[endSquare] = true;
                            board->showQueens()[initSquare] = false;
                            board->showQueens()[endSquare] = true;
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
                            board->showRooks()[endSquare] = false;
                            board->showCurrentColor()[initSquare] = false;
                            board->showAnotherColor()[endSquare] = false;
                            board->showCurrentColor()[endSquare] = true;
                            board->showQueens()[initSquare] = false;
                            board->showQueens()[endSquare] = true;
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
            else{
                std::cerr << "Impossible move\n";
                return;
            }
        }
    }
    else{


        if(move[2] == '-'){
            if(k == 1){
                if((endSquare - initSquare) % 7 == 0){
                    int i = initSquare + 7;
                    for(i; i <= endSquare; i+=7){
                        if(board->showAnotherColor()[i] or board->showCurrentColor()[i]){
                            std::cerr << "Impossible move\n";
                            return;
                        }
                        else if(i == endSquare){
                            board->showCurrentColor()[initSquare] = false;
                            board->showCurrentColor()[endSquare] = true;
                            board->showQueens()[initSquare] = false;
                            board->showQueens()[endSquare] = true;
                            board->passTheMove();
                            return;
                        }
                    }
                }
                else if((endSquare - initSquare) % 9 == 0){
                    int i = initSquare + 9;
                    for(i; i <= endSquare; i+=9){
                        if(board->showAnotherColor()[i] or board->showCurrentColor()[i]){
                            std::cerr << "Impossible move\n";
                            return;
                        }
                        else if(i == endSquare){
                            board->showCurrentColor()[initSquare] = false;
                            board->showCurrentColor()[endSquare] = true;
                            board->showQueens()[initSquare] = false;
                            board->showQueens()[endSquare] = true;
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
                    for(i; i >= endSquare; i-=7){
                        if(board->showAnotherColor()[i] or board->showCurrentColor()[i]){
                            std::cerr << "Impossible move\n";
                            return;
                        }
                        else if(i == endSquare){
                            board->showCurrentColor()[initSquare] = false;
                            board->showCurrentColor()[endSquare] = true;
                            board->showQueens()[initSquare] = false;
                            board->showQueens()[endSquare] = true;
                            board->passTheMove();
                            return;
                        }
                    }
                }
                else if((initSquare - endSquare) % 9 == 0){
                    int i = initSquare - 9;
                    for(i; i >= endSquare; i-=9){
                        if(board->showAnotherColor()[i] or board->showCurrentColor()[i]){
                            std::cerr << "Impossible move\n";
                            return;
                        }
                        else if(i == endSquare){
                            board->showCurrentColor()[initSquare] = false;
                            board->showCurrentColor()[endSquare] = true;
                            board->showQueens()[initSquare] = false;
                            board->showQueens()[endSquare] = true;
                            board->passTheMove();
                            return;
                        }
                    }
                }
                else std::cerr << "Impossible move\n";
            }
        }

        if(move[2] == 'x'){
            if(k == 1){
                if((endSquare - initSquare) % 7 == 0){
                    int i = initSquare + 7;
                    for(i; i <= endSquare; i+=7){
                        if(board->showAnotherColor()[i] or board->showCurrentColor()[i]){
                            std::cerr << "Impossible move\n";
                            return;
                        }
                        else if(i == endSquare){
                            board->showPawns()[endSquare] = false;
                            board->showRooks()[endSquare] = false;
                            board->showKnights()[endSquare] = false;
                            board->showBishops()[endSquare] = false;
                            board->showCurrentColor()[initSquare] = false;
                            board->showAnotherColor()[endSquare] = false;
                            board->showCurrentColor()[endSquare] = true;
                            board->showQueens()[initSquare] = false;
                            board->showQueens()[endSquare] = true;
                            board->passTheMove();
                            return;
                        }
                    }
                }
                else if((endSquare - initSquare) % 9 == 0){
                    int i = initSquare + 9;
                    for(i; i <= endSquare; i+=9){
                        if(board->showAnotherColor()[i] or board->showCurrentColor()[i]){
                            std::cerr << "Impossible move\n";
                            return;
                        }
                        else if(i == endSquare){
                            board->showPawns()[endSquare] = false;
                            board->showRooks()[endSquare] = false;
                            board->showKnights()[endSquare] = false;
                            board->showBishops()[endSquare] = false;
                            board->showCurrentColor()[initSquare] = false;
                            board->showAnotherColor()[endSquare] = false;
                            board->showCurrentColor()[endSquare] = true;
                            board->showQueens()[initSquare] = false;
                            board->showQueens()[endSquare] = true;
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
                    for(i; i >= endSquare; i-=7){
                        if(board->showAnotherColor()[i] or board->showCurrentColor()[i]){
                            std::cerr << "Impossible move\n";
                            return;
                        }
                        else if(i == endSquare){
                            board->showPawns()[endSquare] = false;
                            board->showRooks()[endSquare] = false;
                            board->showKnights()[endSquare] = false;
                            board->showBishops()[endSquare] = false;
                            board->showCurrentColor()[initSquare] = false;
                            board->showAnotherColor()[endSquare] = false;
                            board->showCurrentColor()[endSquare] = true;
                            board->showQueens()[initSquare] = false;
                            board->showQueens()[endSquare] = true;
                            board->passTheMove();
                            return;
                        }
                    }
                }
                else if((initSquare - endSquare) % 9 == 0){
                    int i = initSquare - 9;
                    for(i; i >= endSquare; i-=9){
                        if(board->showAnotherColor()[i] or board->showCurrentColor()[i]){
                            std::cerr << "Impossible move\n";
                            return;
                        }
                        else if(i == endSquare){
                            board->showPawns()[endSquare] = false;
                            board->showRooks()[endSquare] = false;
                            board->showKnights()[endSquare] = false;
                            board->showBishops()[endSquare] = false;
                            board->showCurrentColor()[initSquare] = false;
                            board->showAnotherColor()[endSquare] = false;
                            board->showCurrentColor()[endSquare] = true;
                            board->showQueens()[initSquare] = false;
                            board->showQueens()[endSquare] = true;
                            board->passTheMove();
                            return;
                        }
                    }
                }
                else std::cerr << "Impossible move\n";
            }
        }
        else{
            std::cerr << "Impossible move\n";
            return;
        }
    }
}