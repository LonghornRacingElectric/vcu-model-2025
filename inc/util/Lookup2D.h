//
// Created by henry on 11/10/2024.
//

#ifndef INC_2DLOOKUP_H
#define INC_2DLOOKUP_H

#include <vector>

class 2DLookup {
private:
    float x0 = 0;
    float x1 = 0;
    float y0 = 0;
    float y1 = 0;
    float z[11][11] {};
public:
    2DLookup() = default;
    2DLookup(float x0, float x1, float y0, float y1, float z[11][11]);
    float operator()(float x, float y);
};

#endif //INC_2DLOOKUP_H





