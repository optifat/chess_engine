#ifndef CHESS_ENGINE_INPUT_PROCESSOR_H
#define CHESS_ENGINE_INPUT_PROCESSOR_H

#include <string>
#include "Board.h"

class Input_processor {
public:
    Input_processor();
    ~Input_processor();
    static void readMove(Board* board, std::string move);
};


#endif //CHESS_ENGINE_INPUT_PROCESSOR_H
