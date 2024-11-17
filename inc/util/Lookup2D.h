//
// Created by henry on 11/10/2024.
//

#ifndef INC_Lookup2D_H
#define INC_Lookup2D_H

#include <vector>

class Lookup2D {
private:
    float x0 = 0;
    float x1 = 0;
    float y0 = 0;
    float y1 = 0;
    float z[11][11] {};
public:
    Lookup2D() = default;
    Lookup2D(float x0, float x1, float y0, float y1, float z[11][11]);
    float operator()(float x, float y);
};

#endif //INC_Lookup2D_H





