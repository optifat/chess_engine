#include <iostream>

#include "Moves.h"

int main() {
    std::string FEN = "B6R/2k5/8/P21K3/1N6/8/P7/8 b KQkq -";
    Board board(FEN);
    std::cout << "Print pawn move (e2-e4 for example), the program should return initial and final pieces on these squares \n";
    std::cout << "Print stop to exit the program \n";

    while(true) {
        board.showBoard();
        std::string input;
        std::cin >> input;
        if (input == "stop") {
            break;
        } else {
            readMove(&board, input);
        }
        std::cout << "Enter the next move \n";
    }
    return 0;
}