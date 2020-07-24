#ifndef CHESS_ENGINE_BISHOP_MOVE_H
#define CHESS_ENGINE_BISHOP_MOVE_H

class Bishop_move: public Move{

public:
    Bishop_move();
    void makeMove(Board *board, int initSquare, int endSquare, bool take) override;
};

#endif //CHESS_ENGINE_BISHOP_MOVE_H
