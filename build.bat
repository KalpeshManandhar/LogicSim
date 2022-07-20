@echo off
setlocal
path = dll; %PATH%
g++ -Isrc/include -Lsrc/lib -o test code/graphics.cpp code/input.cpp code/main.cpp code/component.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
test.exe

