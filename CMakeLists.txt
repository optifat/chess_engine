cmake_minimum_required(VERSION 3.8)
project(chess_engine)

set(CMAKE_CXX_STANDARD 11)

set(PIECES_FILES main.cpp pieces/include/Board.h pieces/src/Pawn_move.cpp Moves.h pieces/include/Rook_move.h pieces/include/Knight_move.h pieces/include/Bishop_move.h pieces/src/Board.cpp pieces/include/Move.h pieces/src/Move.cpp pieces/include/Pawn_move.h pieces/src/Rook_move.cpp pieces/src/Bishop_move.cpp pieces/src/Knight_move.cpp pieces/include/Queen_move.h pieces/include/King_move.h pieces/include/Castling.h pieces/src/Queen_move.cpp pieces/src/King_move.cpp pieces/src/Castling.cpp)
set(TREE_FILES tree/include/Node.h tree/src/Node.cpp tree/include/PositionNode.h tree/src/PositionNode.cpp tree/include/tree.h tree/src/tree.cpp tree/include/ValueNode.h tree/src/ValueNode.cpp)

add_executable(chess_engine ${PIECES_FILES} ${TREE_FILES})