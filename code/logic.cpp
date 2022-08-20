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
    if (inputs[in_num] == 0)
        return(0);
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

template <int in_num>
inline int Logic::MUXLogic(int * inputs){
    int i,n,j=0;
    for (n = 5; n>0;n--){
        if (in_num > (1<<n))
            break;
    }
    for (i=n; i>0; i--){
        j = inputs[in_num - i]|(j<<1);
    }
    return(inputs[j]);
}

template <int in_num>
inline int Logic::DEMUXLogic(int * inputs){
    int i,n,j = 0;
    n = 0|inputs[0];
    for (i=1; i<in_num ; i++){
        j = inputs[i]|(j<<1);
    }
    n = n<<((1<<(in_num-1))-1-j);
    return(n);
}

inline int Logic::JKFFLogic(int * inputs, int * outputs){
    int memory = 0;
    memory = memory|(outputs[0]<<1)|outputs[1];
    if (inputs[1] == 1){
        if (inputs[0] == 1 && inputs[2] == 0)
            memory = 2;
        else if (inputs[0] == 0 && inputs[2] == 1)
            memory = 1;
        else if (inputs[0] == 0 && inputs[2] == 0){}
        else if (inputs[0] == 1 && inputs[2] == 1)
            memory = (memory==1)?2:1;
    }
    return(memory);
}

inline int Logic::TFFLogic(int *inputs, int * outputs){
    int memory = 0;
    memory = memory|(outputs[0]<<1)|outputs[1];
    if (memory == 0)
        memory = 2;
    if (inputs[1] == 1){
        if(inputs[0] == 1)
            memory = (memory==1)?2:1;
    }
    return(memory);
}

inline int Logic::SRFFLogic(int *inputs, int * outputs){
    int memory = 0;
    memory = memory|(outputs[0]<<1)|outputs[1];
    if (inputs[1] == 1){
        if (inputs[0] == 1 && inputs[2] == 0)
            memory = 2;
        else if (inputs[0] == 0 && inputs[2] == 1)
            memory = 1;
        else if (inputs[0] == 0 && inputs[2] == 0){}
        else if (inputs[0] == 1 && inputs[2] == 1)
            memory = 0; 
    }
    return(memory);
}


inline int Logic::DFFLogic(int *inputs, int * outputs){
    int memory;
    memory = memory|(outputs[0]<<1)|outputs[1];
    if (inputs[1] == 1){
        if(inputs[0] == 1)
            memory = 2;
        else
            memory = 1;
    }
    return(memory);
}

inline int Logic::SRLatchLogic(int *inputs, int * outputs){
    int memory = 0;
    memory = memory|(outputs[0]<<1)|outputs[1];
    if(inputs[0] == 1 && inputs[1] == 0)
        memory = 2;
    else if (inputs[0] == 0 && inputs[1] == 1)
        memory = 1;
    else if (inputs[0] == 0 && inputs[1] == 1){}
    else if (inputs[0] == 1 && inputs[1] == 1)
        memory = 0;
    return(memory);
}

int Logic::handleLogic(c_type type, int * input, int * output){
    int op = 0;
    // blank (-1) inputs result in 0 output
    if (input[0] == -1 || input[1] == -1)
        return(op);
    
    switch (type)
    {
    case _AND:
        op = ANDLogic(input[0], input[1]);
        break;
    case _OR:
        op = ORLogic(input[0], input[1]);
        break;
    case _NOT:
        op = NOTLogic(input[0]);
        break;
    case _NAND:
        op = NANDLogic(input[0], input[1]);
        break;
    case _NOR:
        op = NORLogic(input[0], input[1]);
        break;
    case _XOR:
        op = XORLogic(input[0], input[1]);
        break;
    case _XNOR:
        op = XNORLogic(input[0], input[1]);
        break;
    case _ADDER:
        op = ADDERLogic(input[0], input[1], input[2]);
        break;
    case _SUBTRACTOR:
        op = SUBTRACTLogic(input[0], input[1], input[2]);
        break;
    case _4x2ENCODER:
        op = ENCODERLogic<4>(input);
        break;
    case _2x4DECODER:
        op = DECODERLogic<2>(input); 
        break;
    case _8x1MUX:
        op = MUXLogic<11>(input);
        break;
    case _1x8DEMUX:
        op = DEMUXLogic<4>(input);
        break;
    case _JKFF:
        op = JKFFLogic(input, output);
        break;
    case _TFF:
        op = TFFLogic(input, output);
        break;
    case _DFF:
        op = DFFLogic(input, output);
        break;
    case _SRFF:
        op = SRFFLogic(input, output);
        break;
    case _SRLATCH:
        op = SRLatchLogic(input, output);
        break;
    default:
        break;
    }
    return(op);
}



