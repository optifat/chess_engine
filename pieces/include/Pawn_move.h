#ifndef CHESS_ENGINE_PAWN_MOVE_H
#define CHESS_ENGINE_PAWN_MOVE_H

#include "Move.h"

class Pawn_move: public Move{

public:
    Pawn_move();
    static bool makeMove(Board& board, int initSquare, int endSquare, bool take, char promotion = ' ');

private:
    static void promotion(Board& board, int endSquare, char promotion);
};

#endif //CHESS_ENGINE_PAWN_MOVE_H
