# Samurai chess engine

## About
This is my hobby project I slowly write from time to time. Right now it might have bugs and performance problems

## Build and run

## Build
This project uses CMake as main build and run. To build it you can use the next commands:<br/>
1.`mkdir build && cd build` -- creating a build directory and navigating to it <br/>
2.`cmake ..` -- configuring generating building files<br/>
3.`cmake --build .` -- building project<br/>
<br/>
To set the position paste FEN Board constructor in main.cpp.
Right now the program doesn't check the FEN correctness, so be careful.
You can generate it [here](https://lichess.org/editor).
The number in tree.generateTree function sets the calculation depth.

## Run

`./chess_engine --flags`  -- running project<br/>
There is a set of flags for executable file:<br/>
1.`-p` or `--playmode` -- turns on the PvP mode
## Computing performance
### Linux
I've tested on Intel(R) Pentium(R) 3558U CPU, compiler was GNU 8.3.0.
The average result was ~525000 generated positions/sec.

### Windows 10

I've tested on i7-8750H CPU with both MSVC 19.28.29337.0 and Clang 10.0 compilers (Visual Studio Community 2019).
Clang: ~880000 position/sec <br/>
MSVC: ~65000 position/sec <br/>
For better experience it's recommended to use Clang compiler in Visual studio.
