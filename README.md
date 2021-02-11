# chess_engine

## About
This is my hobby project I slowly write from time to time. Right now it has no name, but I'll fix that later.
But it has lots of bugs and performance problems (:

## Build and run

This project uses CMake as main build and run. To build it you can use the next commands:<br/>
1.``` mkdir build && cd build # creating a build directory and navigating to it  ``` <br/>
2.``` cmake .. # configuring generating building files```<br/>
3.``` cmake --build . # building project```<br/>
4.``` ./chess_engine # running project```<br/>
<br/>
To set the position paste FEN Board constructor in main.cpp.
Right now the program doesn't check the FEN correctness, so be careful.
You can generate it [here](https://lichess.org/editor).
The number in tree.generateTree function sets the calculation depth.
## Computing performance
### Linux
I've tested on Intel(R) Pentium(R) 3558U CPU, compiler was GNU 8.3.0.
The average result was ~60000 generated positions/sec.

### Windows 10

I've tested on i7-8750H CPU whith both MSVC and Clang compilers (Visual Studio Community 2019).
The results were similar: ~350 positions/sec with current CMakeLists.txt and ~1300 positions/sec with all optimization flags.
Right now I have no clue about reasons of such a bad performance.
