#ifndef CHESS_ENGINE_EVALUATOR_H
#define CHESS_ENGINE_EVALUATOR_H

#include "../../pieces/include/Board.h"

class Evaluator {
public:
    static float evaluatePosition(Board &position);
};


#endif //CHESS_ENGINE_EVALUATOR_H
