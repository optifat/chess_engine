
#ifndef CHESS_ENGINE_MOVES_H
#define CHESS_ENGINE_MOVES_H

#include "Pawn_Move.h"

/* This function will be define by the first letter, which piece should move
 * and pass it over to the next function (pawnMove, queenMove an so on)
 */

void readMove(Board *board, std::string move){
    pawnMove(board, move);
}

#endif //CHESS_ENGINE_MOVES_H


