cmake_minimum_required(VERSION 3.8)
project(chess_engine)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp pieces/include/Board.h pieces/src/Pawn_move.cpp Moves.h pieces/include/Rook_move.h pieces/include/Knight_move.h pieces/include/Bishop_move.h pieces/src/Board.cpp pieces/include/Move.h pieces/src/Move.cpp pieces/include/Pawn_move.h pieces/src/Rook_move.cpp pieces/src/Bishop_move.cpp pieces/src/Knight_move.cpp pieces/include/Queen_move.h pieces/include/King_move.h pieces/include/Castling.h pieces/src/Queen_move.cpp pieces/src/King_move.cpp pieces/src/Castling.cpp)
add_executable(chess_engine ${SOURCE_FILES})