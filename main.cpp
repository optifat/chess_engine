#include "iostream"
#include "Board_Reader.h"

int main() {
    std::string FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -";
    Board_Reader board(FEN);
    std::cout << "Print square (e4 for example), the program should return piece on it \n";
    std::cout << "Print close to stop the program \n";
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