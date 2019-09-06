#include <iostream>
#include "../include/Castling.h"

Castling::Castling(): Move(){};

void Castling::makeMove(Board *board, std::string move) {
    if(move.length() == 3 && move[0] == 'O' && move[2] == 'O' && move[1] == '-'){
        if(board->whiteOrder() && board->whiteShortCastle){
            if(!board->fieldIsAttacked(4) && !board->fieldIsAttacked(5) && !board->fieldIsAttacked(6) &&
               board->showCurrentColor()[4] && board->showKings()[4] &&
               board->showCurrentColor()[7] && board->showRooks()[7] &&
               !board->showCurrentColor()[5] && !board->showCurrentColor()[6] &&
               !board->showAnotherColor()[5] && !board->showAnotherColor()[6])
            {
                board->showRooks()[7] = false;
                board->showCurrentColor()[7] = false;
                board->showRooks()[5] = true;
                board->showCurrentColor()[5] = true;
                board->showKings()[4] = false;
                board->showCurrentColor()[4] = false;
                board->showKings()[6] = true;
                board->showCurrentColor()[6] = true;
                board->passTheMove();
                return;
            }
        }

        else if(!board->whiteOrder() && board->blackShortCastle){
            if(!board->fieldIsAttacked(60) && !board->fieldIsAttacked(61) && !board->fieldIsAttacked(62) &&
               board->showCurrentColor()[60] && board->showKings()[60] &&
               board->showCurrentColor()[63] && board->showRooks()[63] &&
               !board->showCurrentColor()[61] && !board->showCurrentColor()[62] &&
               !board->showAnotherColor()[61] && !board->showAnotherColor()[62])
            {
                board->showRooks()[63] = false;
                board->showCurrentColor()[63] = false;
                board->showRooks()[61] = true;
                board->showCurrentColor()[61] = true;
                board->showKings()[60] = false;
                board->showCurrentColor()[60] = false;
                board->showKings()[62] = true;
                board->showCurrentColor()[62] = true;
                board->passTheMove();
                return;
            }
        }
    }
    else if(move.length() == 5 && move[0] == 'O' && move[2] == 'O' && move[4] == 'O' && move[1] == '-' && move[3] == '-'){
        if(board->whiteOrder() && board->whiteLongCastle){
            if(!board->fieldIsAttacked(2) && !board->fieldIsAttacked(3) && !board->fieldIsAttacked(4) &&
               board->showCurrentColor()[4] && board->showKings()[4] &&
               board->showCurrentColor()[0] && board->showRooks()[0] &&
               !board->showCurrentColor()[1] && !board->showCurrentColor()[2] && !board->showCurrentColor()[3] &&
               !board->showAnotherColor()[1] && !board->showAnotherColor()[2] && !board->showAnotherColor()[3])
            {
                board->showRooks()[0] = false;
                board->showCurrentColor()[0] = false;
                board->showRooks()[3] = true;
                board->showCurrentColor()[3] = true;
                board->showKings()[4] = false;
                board->showCurrentColor()[4] = false;
                board->showKings()[2] = true;
                board->showCurrentColor()[2] = true;
                board->passTheMove();
                return;
            }
        }

        else if(!board->whiteOrder() && board->blackLongCastle){
            if(!board->fieldIsAttacked(58) && !board->fieldIsAttacked(59) && !board->fieldIsAttacked(60) &&
               board->showCurrentColor()[60] && board->showKings()[60] &&
               board->showCurrentColor()[56] && board->showRooks()[56] &&
               !board->showCurrentColor()[57] && !board->showCurrentColor()[58] && !board->showCurrentColor()[59] &&
               !board->showAnotherColor()[57] && !board->showAnotherColor()[58] && !board->showAnotherColor()[59])
            {
                board->showRooks()[56] = false;
                board->showCurrentColor()[56] = false;
                board->showRooks()[59] = true;
                board->showCurrentColor()[59] = true;
                board->showKings()[60] = false;
                board->showCurrentColor()[60] = false;
                board->showKings()[58] = true;
                board->showCurrentColor()[58] = true;
                board->passTheMove();
                return;
            }
        }
    }
    std::cerr << "Impossible move" << std::endl;
}
