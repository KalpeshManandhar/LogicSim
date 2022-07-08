@echo off

g++ -Isrc/include -Lsrc/lib -o test code/graphics.cpp code/input.cpp code/main.cpp -lmingw32 -lSDL2main -lSDL2
.\test.exe