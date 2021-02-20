cmake_minimum_required(VERSION 3.8)
project(Samurai_chess_engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS  "-Ofast -funsafe-math-optimizations -fprofile-use")
#set(CMAKE_CXX_FLAGS "-Wall -Wextra")

set(MAIN main.cpp)
set(PIECES_FILES pieces/include/Input_processor.h pieces/src/Input_processor.cpp
                 pieces/include/Board.h pieces/src/Board.cpp
                 pieces/include/Move.h pieces/src/Move.cpp
                 pieces/include/Pawn_move.h pieces/src/Pawn_move.cpp
                 pieces/include/Bishop_move.h pieces/src/Bishop_move.cpp
                 pieces/include/Knight_move.h pieces/src/Knight_move.cpp
                 pieces/include/Rook_move.h pieces/src/Rook_move.cpp
                 pieces/include/Queen_move.h pieces/src/Queen_move.cpp
                 pieces/include/King_move.h pieces/src/King_move.cpp
                 pieces/include/Castling.h pieces/src/Castling.cpp
        )
set(TREE_FILES tree/include/Node.h tree/src/Node.cpp
               tree/include/Tree.h tree/src/Tree.cpp
               tree/src/Evaluator.cpp tree/include/Evaluator.h)

add_executable(Samurai ${MAIN} ${PIECES_FILES} ${TREE_FILES})
