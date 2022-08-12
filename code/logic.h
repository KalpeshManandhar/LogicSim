#pragma once

#include "utils.h"

class Logic{
public:
    int handleLogic(c_type type, int * input);

    int ANDLogic(int i1, int i2);
    int ORLogic(int i1, int i2);
    int NOTLogic(int i1);
    int NANDLogic(int i1, int i2);
    int NORLogic(int i1, int i2);
    int XORLogic(int i1, int i2);
    int XNORLogic(int i1, int i2);
    int ADDERLogic(int i1, int i2, int i3);
    int SUBTRACTLogic(int i1, int i2, int i3);

    template <int in_num>
    int ENCODERLogic(int * inputs);   
    template <int in_num>
    int DECODERLogic(int * inputs);   
};