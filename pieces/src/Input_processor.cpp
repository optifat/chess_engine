#include <iostream>
#include "../include/Input_processor.h"
#include "../include/Pawn_move.h"
#include "../include/Rook_move.h"
#include "../include/Knight_move.h"
#include "../include/Bishop_move.h"
#include "../include/Queen_move.h"
#include "../include/Castling.h"
#include "../include/King_move.h"

void Input_processor::readMove(Board *board, std::string move) {

    if (move[0] == 'O') {
        Castling nextMove;
        nextMove.makeMove(board, move);
        board->editEnPassant(-1);
        return;
    }

    if(move.length() != 5){
        std::cerr << "Wrong move input (length) \n";
        return;
    } else if(move[2] != '-' && move[2] != 'x'){
        std::cerr << "Wrong move input (not - or x)\n";
        return;
    } else if(move[0] == move[3] || move[1] == move[4]){
        std::cerr << "Impossible move";
        return;
    } else if(move[0]>'h' || move[0]<'a' || move[3]>'h' || move[3]<'a' || move[1]>'8' || move[1]<'1' || move[4]>'8' || move[4]<'1'){
        std::cerr << "Wrong input";
        return;
    }

    int initSquare = move[1] - 'a' + 8*(move[2] - '1');
    int endSquare = move[4] - 'a' + 8*(move[5] - '1');

    if (move[0] >= 'a' && move[0] <= 'h') {
        Pawn_move nextMove;
        if(nextMove.openingPin(board, move)){
            std::cerr << "This piece is pinned\n";
            return;
        }
        nextMove.makeMove(board, move);
    }
    else if (move[0] == 'R') {
        Rook_move nextMove;
        if(nextMove.openingPin(board, move.substr(1, 5))){
            std::cerr << "This piece is pinned\n";
            return;
        }
        nextMove.makeMove(board, move.substr(1, 5));
        board->editEnPassant(-1);

    }
    else if (move[0] == 'N') {
        Knight_move nextMove;
        if(nextMove.openingPin(board, move.substr(1, 5))){
            std::cerr << "This piece is pinned\n";
            return;
        }
        nextMove.makeMove(board, move.substr(1, 5));
        board->editEnPassant(-1);
    }
    else if (move[0] == 'B') {
        Bishop_move nextMove;
        if(nextMove.openingPin(board, move.substr(1, 5))){
            std::cerr << "This piece is pinned\n";
            return;
        }
        if(!board->bishops[initSquare] or !board->showCurrentColor()[initSquare]) {
            std::cerr << "No bishop on " << move[0] << move[1] << "\n";
            return;
        }
        nextMove.makeMove(board, move.substr(1, 5));
        board->editEnPassant(-1);
    }
    else if (move[0] == 'Q') {
        Queen_move nextMove;
        if(nextMove.openingPin(board, move.substr(1, 5))){
            std::cerr << "This piece is pinned\n";
            return;
        }
        nextMove.makeMove(board, move.substr(1, 5));
        board->editEnPassant(-1);
    }
    else if (move[0] == 'O') {
        Castling nextMove;
        nextMove.makeMove(board, move);
        board->editEnPassant(-1);
    }
    else if (move[0] == 'K') {
        King_move nextMove;
        nextMove.makeMove(board, move.substr(1, 5));
        board->editEnPassant(-1);
    }
}