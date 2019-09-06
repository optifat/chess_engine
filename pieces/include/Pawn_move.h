#ifndef CHESS_ENGINE_PAWN_MOVE_H
#define CHESS_ENGINE_PAWN_MOVE_H

#include "Move.h"

class Pawn_move: public Move{

public:
    Pawn_move();
    void makeMove(Board *board, std::string move) override;

private:
    void promotion(Board *board, int endSquare);
};

#endif //CHESS_ENGINE_PAWN_MOVE_H
