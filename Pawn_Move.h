#ifndef CHESS_ENGINE_MOVE_READER_H
#define CHESS_ENGINE_MOVE_READER_H

#include <iostream>
#include "Board.h"

void pawnMove(Board *board, std::string move){
    if(move.length() != 5){
        std::cerr << "Wrong move input (length) \n";
        return;
    } else if(move[2] != '-' and move[2] != 'x'){
        std::cerr << "Wrong move input (not - or x)\n";
        return;
    } else if(move[0]>'h' or move[0]<'a' or move[3]>'h' or move[3]<'a'){
        std::cerr << "Wrong verticals, should be a-h \n";
        return;
    } else if(move[1]>'8' or move[1]<'1' or move[1]>'8' or move[3]<'1'){
        std::cerr << "Wrong horizontals, should be 1-8 \n";
        return;
    }

    int initSquare = move[0] - 'a' + 8*(move[1] - '1');
    int endSquare = move[3] - 'a' + 8*(move[4] - '1');

    if(!board->showPawns()[initSquare] or !board->showCurrentColor()){
        std::cerr << "No pawn on " << move[0] << move[1]<<"\n";
        return;
    }

    /* k variable is defined by the side to move: 1 if white and -1 if black.
     * All the white pawns are going up the board while black vice versa.
     * That means for us, that the difference between end and initial pawn squares is positive in case of white
     * and negative in case of black.
     * Also, in case of A or H verticals, the possible takes are only to vertical B and G respectively.
     * As example for A vertical:
     *      white pawn move: A(i) x B(i+1), the difference between end and initial pawn squares is 9
     *      black pawn move: A(i) x B(i-1), the difference between end and initial pawn squares is -7
     * So the possible difference can be defined as (8 + k)*k
     * Similarly for H vertical with change of previous equation to (8 - k)*k
     */

    int k = 0;
    if(board->whiteOrder())
        k = 1;
    else
        k = -1;

    if(move[2] == '-'){
        if((move[1] == '2' and endSquare - initSquare == 16*k) or (move[1] == '7' and endSquare - initSquare == 16*k)
           and !board->showCurrentColor()[endSquare] and !board->showCurrentColor()[endSquare-8*k]
           and !board->showAnotherColor()[endSquare] and !board->showAnotherColor()[endSquare-8*k]){
            board->showCurrentColor()[initSquare] = false;
            board->showCurrentColor()[endSquare]  = true;
            board->showPawns()[initSquare] = false;
            board->showPawns()[endSquare] = true;
            board->passTheMove();
            return;
        } else if(endSquare - initSquare == 8*k
                  and !board->showCurrentColor()[endSquare] and !board->showAnotherColor()[endSquare]){
            board->showCurrentColor()[initSquare] = false;
            board->showCurrentColor()[endSquare]  = true;
            board->showPawns()[initSquare] = false;
            board->showPawns()[endSquare] = true;
            board->passTheMove();
            return;
        } else{
            std::cerr << "Impossible move \n";
            return;
        }
    } else if(move[2] == 'x' and !board->showAnotherColor()){
        std::cerr << "Nothing to take on "+move[3]+move[4]+'\n';
        return;
    } else if(move[2] == 'x') {
        //checking vertical a
        if (initSquare % 8 == 0 and endSquare - initSquare == (8 + k)*k) {
            board->showCurrentColor()[initSquare] = false;
            board->showCurrentColor()[endSquare] = true;
            board->showAnotherColor()[endSquare] = false;
            board->showPawns()[initSquare] = false;
            board->showPawns()[endSquare] = true;
            board->showBishops()[endSquare] = false;
            board->showRooks()[endSquare] = false;
            board->showKnights()[endSquare] = false;
            board->showQueens()[endSquare] = false;
            board->passTheMove();
            return;
        }
        //now we checking vertical h
        else if (initSquare % 8 == 7 and endSquare - initSquare == (8 - k)*k) {
            board->showCurrentColor()[initSquare] = false;
            board->showCurrentColor()[endSquare] = true;
            board->showAnotherColor()[endSquare] = false;
            board->showPawns()[initSquare] = false;
            board->showPawns()[endSquare] = true;
            board->showBishops()[endSquare] = false;
            board->showRooks()[endSquare] = false;
            board->showKnights()[endSquare] = false;
            board->showQueens()[endSquare] = false;
            board->passTheMove();
            return;
        }
        //all other verticals
        else if (endSquare - initSquare == 7*k or endSquare - initSquare == 9*k) {
            board->showCurrentColor()[initSquare] = false;
            board->showCurrentColor()[endSquare] = true;
            board->showAnotherColor()[endSquare] = false;
            board->showPawns()[initSquare] = false;
            board->showPawns()[endSquare] = true;
            board->showBishops()[endSquare] = false;
            board->showRooks()[endSquare] = false;
            board->showKnights()[endSquare] = false;
            board->showQueens()[endSquare] = false;
            board->passTheMove();
            return;
        } else{
            std::cerr << "Impossible take \n";
            return;
        }
    }
}


#endif //CHESS_ENGINE_MOVE_READER_H
