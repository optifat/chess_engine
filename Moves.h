
#ifndef CHESS_ENGINE_MOVES_H
#define CHESS_ENGINE_MOVES_H

#include "Pawn_Move.h"
#include "Rook_move.h"

/* This function will be define by the first letter, which piece should move
 * and pass it over to the next function (pawnMove, queenMove an so on)
 */

void readMove(Board *board, std::string move){
    if (move[0] >= 'a' and move[0] <= 'h')
        pawnMove(board, move);
    else if (move[0] == 'R')
        rookMove(board, move.substr(1, 5));
}

#endif //CHESS_ENGINE_MOVES_H


