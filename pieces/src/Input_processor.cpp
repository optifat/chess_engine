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

    if (move[0] == '0') {
        if(!move.compare("0-0")){
            Castling::makeMove(board, 56*!board->whiteOrder()+4, 56*!board->whiteOrder()+6);
        }
        else if(!move.compare("0-0-0")){
            Castling::makeMove(board, 56*!board->whiteOrder()+4, 56*!board->whiteOrder()+2);
        }

        board->editEnPassant(-1);
        return;
    }

    char pieceType;
    if(move.length() == 6){
        pieceType = move[0];
        move = move.substr(1, 5);
    }
    else if(move.length() == 5){
        pieceType = 'p';
    }
    else{
        std::cerr << "Wrong move input (length) \n";
        return;
    }

    bool take;
    if(move[2] == 'x'){
        take = true;
    }
    else if(move[2] == '-'){
        take = false;
    }
    else{
        std::cerr << "Wrong move input (not - or x)\n";
        return;
    }

    if(move[0]>'h' || move[0]<'a' || move[3]>'h' || move[3]<'a' || move[1]>'8' || move[1]<'1' || move[4]>'8' || move[4]<'1'){
        std::cerr << "Wrong input\n";
        return;
    }

    int initSquare = move[0] - 'a' + 8*(move[1] - '1');
    int endSquare = move[3] - 'a' + 8*(move[4] - '1');

    if(initSquare == endSquare){
        std::cerr << "Impossible move: squares must be different\n";
        return;
    }

    int kingPos = -1;
    for(int i = 0; i <= 63; i++){
        if(board->kingCheck(i) && board->currentColorCheck(i)){
            kingPos = i;
            break;
        }
    }

    if(board->fieldAttackers(kingPos).size() >= 2 && pieceType != 'K'){
        std::cerr << "King is checked" << std::endl;
        return;
    }
    else if(board->fieldAttackers(kingPos).size() == 1 && pieceType != 'K'){
        if(endSquare != board->fieldAttackers(kingPos)[0]){
            board->updateCurrentColor(initSquare, endSquare);
            if(board->fieldIsAttacked(kingPos)){
                board->updateCurrentColor(endSquare, initSquare);
                std::cerr << "King is checked" << std::endl;
                return;
            }
            board->updateCurrentColor(endSquare, initSquare);
        }
    }

    std::cout << "Init: " << initSquare << ", end: " << endSquare << ", piece type: " << pieceType << ", take: " << take << std::endl;

    if(take && !board->anotherColorCheck(endSquare) && !(pieceType == 'p' && endSquare == board->possibleEnPassant())){
        std::cerr << "Nothing to take there\n";
    }

    if (pieceType == 'p') {
        if(Move::openingPin(board, initSquare, endSquare)){
            std::cerr << "This piece is pinned\n";
            return;
        }
        if(!board->pawnCheck(initSquare) || !board->currentColorCheck(initSquare)) {
            std::cerr << "No pawn on " << move[0] << move[1] << " square\n";
            return;
        }
        auto result = Pawn_move::makeMove(board, initSquare, endSquare, take, ' ');
        if (!result){
            std::cerr << "Impossible move" << std::endl;
        }

    }
    else if (pieceType == 'R') {
        if(Move::openingPin(board, initSquare, endSquare)){
            std::cerr << "This piece is pinned\n";
            return;
        }
        if(!board->rookCheck(initSquare) || !board->currentColorCheck(initSquare)) {
            std::cerr << "No rook on " << move[0] << move[1] << " square\n";
            return;
        }
        auto result = Rook_move::makeMove(board, initSquare, endSquare);
        if (!result){
            std::cerr << "Impossible move" << std::endl;
        }
        board->editEnPassant(-1);

    }
    else if (pieceType == 'N') {
        if(Move::openingPin(board, initSquare, endSquare)){
            std::cerr << "This piece is pinned\n";
            return;
        }
        if(!board->knightCheck(initSquare) || !board->currentColorCheck(initSquare)) {
            std::cerr << "No knight on " << move[0] << move[1] << " square\n";
            return;
        }
        Knight_move::makeMove(board, initSquare, endSquare);
        board->editEnPassant(-1);
    }
    else if (pieceType == 'B') {
        if(Move::openingPin(board, initSquare, endSquare)){
            std::cerr << "This piece is pinned\n";
            return;
        }
        if(!board->bishopCheck(initSquare) || !board->currentColorCheck(initSquare)) {
            std::cerr << "No bishop on " << move[0] << move[1] << " square\n";
            return;
        }
        if(abs(initSquare%8 - endSquare%8) != abs(initSquare/8-endSquare/8)){
            std::cerr << "Impossible move\n";
            return;
        }
        auto result = Bishop_move::makeMove(board, initSquare, endSquare);
        if (!result){
            std::cerr << "Impossible move" << std::endl;
        }
        board->editEnPassant(-1);
    }
    else if (pieceType == 'Q') {
        if(Move::openingPin(board, initSquare, endSquare)){
            std::cerr << "This piece is pinned\n";
            return;
        }
        if(!board->queenCheck(initSquare) || !board->currentColorCheck(initSquare)) {
            std::cerr << "No queen on " << move[0] << move[1] << " square\n";
            return;
        }
        auto result = Queen_move::makeMove(board, initSquare, endSquare);
        if (!result){
            std::cerr << "Impossible move" << std::endl;
        }
        board->editEnPassant(-1);
    }
    else if (pieceType == 'K') {
        if(!board->kingCheck(initSquare) || !board->currentColorCheck(initSquare)) {
            std::cerr << "No king on " << move[0] << move[1] << " square\n";
            return;
        }
        auto result = King_move::makeMove(board, initSquare, endSquare);
        if (!result){
            std::cerr << "Impossible move" << std::endl;
        }
        board->editEnPassant(-1);
    }
    else{
        std::cerr << "Wrong input: there is no such piece\n";
        return;
    }
}
