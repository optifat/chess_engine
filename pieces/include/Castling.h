#ifndef CHESS_ENGINE_CASTLING_H
#define CHESS_ENGINE_CASTLING_H

#include "Move.h"

class Castling: public Move{
public:
    Castling();
    void makeMove(Board *board, std::string move) override;
};

#endif //CHESS_ENGINE_CASTLING_H
