@echo off

g++ -Iinclude -Llib -o test src/graphics.cpp src/input.cpp src/main.cpp -lmingw32 -lSDL2main -lSDL2