#include <iostream>
#include <chrono>
#include "pieces/include/Input_processor.h"

int main() {
    std::string FEN = "8/7b/8/8/8/8/8/B7 w - - 0 1";
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
            auto start = std::chrono::high_resolution_clock::now();
            Input_processor::readMove(&board, input);
            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "Duration: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
            << " microseconds" << std::endl;
        }
    }
    //board.showBoard();
    //std::cout << sizeof(board) << "\n";
    return 0;
}
