#include "Moves.h"

int main() {
    std::string FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -";
    Board board(FEN);
    std::cout << "Print pawn move (e2-e4 for example), the program should return initial and final pieces on these squares \n";
    std::cout << "Print stop to exit the program \n";
    while(true){
        board.showBoard();
        std::string input;
        std::cin >> input;
        if(input == "stop"){
            break;
        }
        else{
            readMove(&board, input);
        }
        std::cout << "Enter the next move \n";
    }
    return 0;
}