#include "iostream"
#include "Board_Reader.h"
#include "Position_Evaluator.h"

int main() {
    std::string FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -";
    Board_Reader board(FEN);
    std::cout << "Print square (e4 for example), the program should return piece on it \n";
    std::cout << "Print stop to exit the program \n";
    while(true){
        std::string input;
        std::cin >> input;
        if(input == "stop"){
            break;
        }
        else{
            std::cout << board.pieceOnSquare(input) + "\n";
        }
    }
    return 0;
}