#include "logic.h"

inline int Logic::ANDLogic(int i1, int i2){
    // if (i1 == 0 || i2 == 0)
    //     return(0);
    // return(1);

    return(i1 & i2);
}

inline int Logic::ORLogic(int i1, int i2){
    return(i1 | i2);
}

inline int Logic::NOTLogic(int i1){
    if (i1 == 0)
        return(1);
    return(0);
}

inline int Logic::NANDLogic(int i1, int i2){
    return(NOTLogic(i1 & i2));
}

inline int Logic::NORLogic(int i1, int i2){
    return(NOTLogic(i1 | i2));
}

inline int Logic::XORLogic(int i1, int i2){
    if (i1 == i2)
        return(0);
    return(1);
}

inline int Logic::XNORLogic(int i1, int i2){
    if (i1 == i2)
        return(1);
    return(0);
}

int Logic::handleLogic(c_type type, int * input){
    int output = 0;
    switch (type)
    {
    case _AND:
        output = ANDLogic(input[0], input[1]);
        break;
    case _OR:
        output = ORLogic(input[0], input[1]);
        break;
    case _NOT:
        output = NOTLogic(input[0]);
        break;
    case _NAND:
        output = NANDLogic(input[0], input[1]);
        break;
    case _NOR:
        output = NORLogic(input[0], input[1]);
        break;
    case _XNOR:
        output = XNORLogic(input[0], input[1]);
        break;
    default:
        break;
    }
    return(output);
    
}



