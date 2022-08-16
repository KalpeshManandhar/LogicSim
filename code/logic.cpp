#include "logic.h"

inline int Logic::ANDLogic(int i1, int i2){
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
    return(i1 ^ i2);
}

inline int Logic::XNORLogic(int i1, int i2){
    return(NOTLogic(i1 ^ i2));
}

// these functions create a bit mask of the outputs because why not
inline int Logic::ADDERLogic(int i1, int i2, int i3){
    return(i1+i2+i3);
}

inline int Logic::SUBTRACTLogic(int i1, int i2, int i3){
    return(i1-i2-i3);
}

template <int in_num>
inline int Logic::ENCODERLogic(int * inputs){
    int i, j=0;
    for (i=0; i<in_num; i++){
        if (inputs[i] == 1)
            j=j|i;
    }
    return(j);
}

template <int in_num>
inline int Logic::DECODERLogic(int * inputs){
    int i,j=0,k=1;
    for (i=0; i<in_num; i++){
        j = (j<<1)|inputs[i];
        k<<=2;
    }
    k>>=1;
    for (i =0; i<j;i++){
        k>>=1;
    }
    return(k);
}

int Logic::handleLogic(c_type type, int * input){
    int output = 0;
    // blank (-1) inputs result in 0 output
    if (input[0] == -1 || input[1] == -1)
        return(output);
    
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
    case _XOR:
        output = XORLogic(input[0], input[1]);
        break;
    case _XNOR:
        output = XNORLogic(input[0], input[1]);
        break;
    case _ADDER:
        output = ADDERLogic(input[0], input[1], input[2]);
        break;
    case _SUBTRACTOR:
        output = SUBTRACTLogic(input[0], input[1], input[2]);
        break;
    case _4x2ENCODER:
        output = ENCODERLogic<4>(input);
        break;
    case _2x4DECODER:
        output = DECODERLogic<2>(input); 
        break;
    default:
        break;
    }
    return(output);
    
}



