#include <iostream>

#include "../include/King_move.h"

King_move::King_move(): Move(){};

void King_move::makeMove(Board *board, std::string move) {
    if(move.length() != 5){
        std::cerr << "Wrong move input (length) \n";
        return;
    }else if(move[2] != '-' && move[2] != 'x'){
        std::cerr << "Wrong move input (not - or x)\n";
        return;
    } else if(move[0]>'h' || move[0]<'a' || move[3]>'h' || move[3]<'a'){
        std::cerr << "Wrong verticals, should be a-h \n";
        return;
    } else if(move[1]>'8' || move[1]<'1' || move[4]>'8' || move[4]<'1'){
        std::cerr << "Wrong horizontals, should be 1-8 \n";
        return;
    }
    int initSquare = move[0] - 'a' + 8*(move[1] - '1');
    int endSquare = move[3] - 'a' + 8*(move[4] - '1');

    if(!board->showKings()[initSquare] || !board->showCurrentColor()[initSquare]){
        std::cerr << "No king on " << move[0] << move[1]<<"\n";
        return;
    } else if(initSquare == endSquare){
        std::cerr << "Impossible move\n";
        return;
    }

    if(board->fieldIsAttacked(endSquare)){
        std::cerr << "Impossible move\n";
    }

    if(abs(initSquare/8-endSquare/8) > 1 || abs(initSquare%8-endSquare%8) > 1){
        std::cerr << "Impossible move\n";
    }

    if(move[2] == '-'){
        board->showCurrentColor()[initSquare] = false;
        board->showCurrentColor()[endSquare] = true;
        board->showKings()[initSquare] = false;
        board->showKings()[endSquare] = true;
        board->passTheMove();
        return;
    }
    else if(move[2] == 'x'){
        board->showPawns()[endSquare] = false;
        board->showBishops()[endSquare] = false;
        board->showKnights()[endSquare] = false;
        board->showRooks()[endSquare] = false;
        board->showCurrentColor()[initSquare] = false;
        board->showAnotherColor()[endSquare] = false;
        board->showCurrentColor()[endSquare] = true;
        board->showKings()[initSquare] = false;
        board->showKings()[endSquare] = true;
        board->passTheMove();
        return;
    }
}
