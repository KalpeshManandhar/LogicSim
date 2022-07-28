#pragma once

struct vec2{        // 2d vector for coordinates 
    int x,y;
};

enum Pin_type{
    _IN, _OUT, _BLANKE
};

struct Pin{
    vec2 *pos;
    Pin_type type;
};