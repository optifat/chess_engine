#ifndef CHESS_ENGINE_BISHOP_MOVE_H
#define CHESS_ENGINE_BISHOP_MOVE_H

class Bishop_move: public Move{

public:
    Bishop_move();
    static bool makeMove(Board& board, int initSquare, int endSquare);
};

#endif //CHESS_ENGINE_BISHOP_MOVE_H
