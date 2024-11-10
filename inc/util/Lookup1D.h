#ifndef VCU_CORE_1DLOOKUP_H
#define VCU_CORE_1DLOOKUP_H


#include <vector>


class 1DLookup {
private:
    float x0 = 0;
    float x1 = 0;
    float n = 10.0;
    float y[];

public:
    1DLookup() = default; // y = 1
    1DLookup(float x0, float x1, float y[], float n);

    1DLookup(float xP, float yP); // y = kx
    1DLookup(float xP, float yP, float n); // y = kx
    float operator()(float x);
};


#endif //VCU_CORE_CURVEPARAMETER_H