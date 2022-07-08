@echo off
setlocal
path = E:\Programming\Cpp\Project2\LogicSim\dll; %PATH%
g++ -Isrc/include -Lsrc/lib -o test code/graphics.cpp code/input.cpp code/main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
.\test.exe