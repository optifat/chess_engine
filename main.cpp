#include <iostream>

#include "pieces/include/Input_processor.h"

int main() {
    std::string FEN = "8/4N1pk/8/7R/8/8/8/K7 b - - 0 1";
    Board board(FEN);
    std::cout << "Print pawn move (e2-e4 for example), the program should return initial and final pieces on these squares \n";
    std::cout << "Print stop to exit the program \n";

    while(true) {
        board.printInfo();
        board.showBoard();
        if(board.checkmate()){
            std::cout << "Checkmate.";
            if(board.whiteOrder()){
                std::cout << "Black wins." << std::endl;
                return 0;
            }
            else{
                std::cout << "White wins." << std::endl;
                return 0;
            }
        }
        else if(board.stalemate()){
            std::cout << "Stalemate. Draw.";
            return 0;
        }
        std::cout << board.sideToMove() << std::endl;
        std::string input;
        std::cin >> input;
        if (input == "stop") {
            break;
        } else {
            Input_processor::readMove(&board, input);
        }
    }
    //board.showBoard();
    //std::cout << sizeof(board) << "\n";
    return 0;
}
