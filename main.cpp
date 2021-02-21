#include <iostream>
#include <chrono>
#include "pieces/include/Input_processor.h"
#include "tree/include/Tree.h"
#include "tree/include/Evaluator.h"

int main(int argc, char* argv[]) {

    bool analysisMode = true;

    for(int i = 1; i < argc; i++){;
        auto flag = std::string(argv[i]);
        if(flag == "-p" || flag == "--playmode"){
            analysisMode = false;
        }
        else{
            std::cout << "Ignoring unknown " << flag << " flag\n";
        }
    }

    std::cout << "Enter FEN (leave empty for starting position)\n";
    std::string FEN;
    getline(std::cin, FEN);
    if(FEN.empty()){
        FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq";
    }
    //std::string FEN = "K4BB1/1Q6/5p2/8/2R2r1r/N2N2q1/kp1p1p1p/b7 w - - 0 1";
    Board board(FEN);

    if(analysisMode){
        std::cout << "Enter desired tree depth: \n";
        int treeDepth = 1;
        std::cin >> treeDepth;
        Tree tree(std::make_shared<Board>(board));
        auto start = std::chrono::high_resolution_clock::now();
        tree.generateTree(treeDepth);
        auto end = std::chrono::high_resolution_clock::now();
        if (MAX_POS_VAL - abs(tree.getPositionValue()) < 100) {
            std::cout << "#" << ((tree.getPositionValue() > 0) ?
            (MAX_POS_VAL - tree.getPositionValue()) : (-MAX_POS_VAL - tree.getPositionValue())) << std::endl;
        }
        else {
            std::cout << tree.getPositionValue() << std::endl;
        }
        tree.optimalSequence();
        std::cout << "Total nodes generated: " << tree.totalNodesGenerated() << std::endl;
        std::cout << "Total tree generation time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
                  << " microseconds" << std::endl;
        std::cout << 1000000*(double)tree.totalNodesGenerated() / std::chrono::duration_cast<std::chrono::microseconds>(end-start).count() <<
        " nodes per sec" << std::endl;
    }
    else {
        std::cout << "Print pawn move (e2-e4 for example), the program should return initial and final pieces on these squares \n";
        std::cout << "Print stop to exit the program \n";
        while(true) {
            board.printInfo();
            board.showBoard();
            if(board.checkmate()){
                std::cout << "Checkmate. ";
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
                Input_processor::readMove(board, input);
                auto end = std::chrono::high_resolution_clock::now();
                std::cout << "Duration: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
                << " microseconds" << std::endl;

            }
        }
    }
    /*board.showBoard();
    std::cout << sizeof(board) << "\n";*/
    return 0;
}
