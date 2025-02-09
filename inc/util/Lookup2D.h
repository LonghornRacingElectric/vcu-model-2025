//
// Created by henry on 11/10/2024.
//

#ifndef INC_Lookup2D_H
#define INC_Lookup2D_H

#include <vector>

typedef struct Lookup2D {
    float x0 = 0;
    float x1 = 0;
    float y0 = 0;
    float y1 = 0;
    float z[11][11] {};
} Lookup2D;

void Lookup2D_init(Lookup2D* lookup2d, float x0, float x1, float y0, float y1, float z[11][11]);
float Lookup2D_evaluate(Lookup2D* lookup2d, float x, float y);

// class Lookup2D {
// private:
//     float x0 = 0;
//     float x1 = 0;
//     float y0 = 0;
//     float y1 = 0;
//     float z[11][11] {};
// public:
//     Lookup2D() = default;
//     Lookup2D(float x0, float x1, float y0, float y1, float z[11][11]);
//     float operator()(float x, float y);
// };

#endif //INC_Lookup2D_H





