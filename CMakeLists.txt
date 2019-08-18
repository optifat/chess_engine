cmake_minimum_required(VERSION 3.8)
project(chess_engine)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp include/Board.h src/Pawn_move.cpp Moves.h include/Rook_move.h include/Knight_move.h include/Bishop_move.h src/Board.cpp include/Move.h src/Move.cpp include/Pawn_move.h src/Rook_move.cpp src/Bishop_move.cpp src/Knight_move.cpp)
add_executable(chess_engine ${SOURCE_FILES})