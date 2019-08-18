#ifndef CHESS_ENGINE_MOVES_H
#define CHESS_ENGINE_MOVES_H

#include "include/Pawn_move.h"
#include "include/Rook_move.h"
#include "include/Knight_move.h"
#include "include/Bishop_move.h"


/* This function will be define by the first letter, which piece should move
 * and pass it over to the next function (pawnMove, queenMove an so on)
 */

void readMove(Board *board, std::string move){
    if (move[0] >= 'a' and move[0] <= 'h') {
        Pawn_move nextMove;
        nextMove.makeMove(board, move);
    }
    else if (move[0] == 'R') {
        Rook_move nextMove;
        nextMove.makeMove(board, move.substr(1, 5));
    }
    else if (move[0] == 'N') {
        Knight_move nextMove;
        nextMove.makeMove(board, move.substr(1, 5));
    }
    else if (move[0] == 'B') {
        Bishop_move nextMove;
        nextMove.makeMove(board, move.substr(1, 5));
    }
    else if (move[0] == 'Q') {
        //rookMove(board, move.substr(1, 5));
        //bishopMove(board, move.substr(1, 5));
    }
}

#endif //CHESS_ENGINE_MOVES_H


