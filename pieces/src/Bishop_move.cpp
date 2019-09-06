#include <iostream>
#include <cmath>

#include "../include/Board.h"
#include "../include/Move.h"
#include "../include/Bishop_move.h"

// Bishop move has a "Ba1-h8" representation.
// Bishop capturing is similar to pawn capturing e.g. "Ba1xh8".

Bishop_move::Bishop_move(): Move(){};

void Bishop_move::makeMove(Board *board, std::string move){
    if(move.length() != 5){
        std::cerr << "Wrong move input (length) \n";
        return;
    } else if(move[2] != '-' and move[2] != 'x'){
        std::cerr << "Wrong move input (not - or x)\n";
        return;
    } else if(move[0] == move[3] or move[1] == move[4]){
        std::cerr << "Impossible move";
        return;
    } else if(move[0]>'h' or move[0]<'a' or move[3]>'h' or move[3]<'a' or move[1]>'8' or move[1]<'1' or move[4]>'8' or move[4]<'1'){
        std::cerr << "Wrong input";
        return;
    }

    int initSquare = move[0] - 'a' + 8*(move[1] - '1');
    int endSquare = move[3] - 'a' + 8*(move[4] - '1');

    if(!board->showBishops()[initSquare] or !board->showCurrentColor()[initSquare]){
        std::cerr << "No bishop on " << move[0] << move[1]<<"\n";
        return;
    } else if(initSquare == endSquare || abs(initSquare/8-endSquare/8) != abs(initSquare%8-endSquare%8)){
        std::cerr << "Impossible move\n";
        return;
    }

    // k variable shows "move direction".
    int k = 1;
    if(initSquare > endSquare)
        k = -1;

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
                        board->showBishops()[initSquare] = false;
                        board->showBishops()[endSquare] = true;
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
                        board->showBishops()[initSquare] = false;
                        board->showBishops()[endSquare] = true;
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
                        board->showBishops()[initSquare] = false;
                        board->showBishops()[endSquare] = true;
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
                        board->showBishops()[initSquare] = false;
                        board->showBishops()[endSquare] = true;
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
                    if(board->showCurrentColor()[i]){
                        std::cerr << "Impossible move1\n";
                        return;
                    }
                    else if(i == endSquare){
                        board->showPawns()[endSquare] = false;
                        board->showRooks()[endSquare] = false;
                        board->showKnights()[endSquare] = false;
                        board->showQueens()[endSquare] = false;
                        board->showCurrentColor()[initSquare] = false;
                        board->showAnotherColor()[endSquare] = false;
                        board->showCurrentColor()[endSquare] = true;
                        board->showBishops()[initSquare] = false;
                        board->showBishops()[endSquare] = true;
                        board->passTheMove();
                        return;
                    }
                }
            }
            else if((endSquare - initSquare) % 9 == 0){
                int i = initSquare + 9;
                for(i; i <= endSquare; i+=9){
                    if(board->showAnotherColor()[i] or board->showCurrentColor()[i]){
                        std::cerr << "Impossible move2\n";
                        return;
                    }
                    else if(i == endSquare){
                        board->showPawns()[endSquare] = false;
                        board->showRooks()[endSquare] = false;
                        board->showKnights()[endSquare] = false;
                        board->showQueens()[endSquare] = false;
                        board->showCurrentColor()[initSquare] = false;
                        board->showAnotherColor()[endSquare] = false;
                        board->showCurrentColor()[endSquare] = true;
                        board->showBishops()[initSquare] = false;
                        board->showBishops()[endSquare] = true;
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
                for(i; i >= endSquare; i-=7){
                    if(board->showAnotherColor()[i] or board->showCurrentColor()[i]){
                        std::cerr << "Impossible move\n";
                        return;
                    }
                    else if(i == endSquare){
                        board->showPawns()[endSquare] = false;
                        board->showRooks()[endSquare] = false;
                        board->showKnights()[endSquare] = false;
                        board->showQueens()[endSquare] = false;
                        board->showCurrentColor()[initSquare] = false;
                        board->showAnotherColor()[endSquare] = false;
                        board->showCurrentColor()[endSquare] = true;
                        board->showBishops()[initSquare] = false;
                        board->showBishops()[endSquare] = true;
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
                        board->showQueens()[endSquare] = false;
                        board->showCurrentColor()[initSquare] = false;
                        board->showAnotherColor()[endSquare] = false;
                        board->showCurrentColor()[endSquare] = true;
                        board->showBishops()[initSquare] = false;
                        board->showBishops()[endSquare] = true;
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

