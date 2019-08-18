#include <iostream>
#include <cmath>
#include <set>

#include "../include/Board.h"
#include "../include/Move.h"
#include "../include/Knight_move.h"


Knight_move::Knight_move(): Move(){};

void Knight_move::makeMove(Board *board, std::string move){
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
    std::set<int> possibleMoves = {-17, -15, -10, -6, 6, 10, 15, 17};

    if(!board->showKnights()[initSquare] or !board->showCurrentColor()[initSquare]){
        std::cerr << "No knight on " << move[0] << move[1]<<"\n";
        return;
    } else if(possibleMoves.find(initSquare - endSquare) == possibleMoves.end()){
        std::cerr << "Impossible move\n";
        return;
    } else if(abs(initSquare/8-endSquare/8)+abs(initSquare%8-endSquare%8) != 3){  //need to think how to deal with impossible moves like Na8-g8
        std::cerr << "Impossible move\n";
        return;
    }

    std::cout << endSquare/8 - initSquare/8 << ' ' << (initSquare-endSquare+1)/8 << std::endl;

    if(move[2] == '-'){
        board->showCurrentColor()[initSquare] = false;
        board->showCurrentColor()[endSquare]  = true;
        board->showKnights()[initSquare] = false;
        board->showKnights()[endSquare] = true;
        board->passTheMove();
    }
    else if(move[2] == 'x'){
        board->showCurrentColor()[initSquare] = false;
        board->showCurrentColor()[endSquare] = true;
        board->showAnotherColor()[endSquare] = false;
        board->showKnights()[initSquare] = false;
        board->showKnights()[endSquare] = true;
        board->showPawns()[endSquare] = false;
        board->showBishops()[endSquare] = false;
        board->showRooks()[endSquare] = false;
        board->showQueens()[endSquare] = false;
    }
    else{
        std::cerr << "Impossible move\n";
        return;
    }
}

