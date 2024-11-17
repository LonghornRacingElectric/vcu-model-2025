#ifndef VCU_CORE_Lookup1D_H
#define VCU_CORE_Lookup1D_H


#include <vector>


class Lookup1D {
private:
    float x0 = 0;
    float x1 = 0;
    float n = 10.0;
    float y[];

public:
    Lookup1D() = default; // y = 1
    Lookup1D(float x0, float x1, float y[], float n);

    Lookup1D(float xP, float yP); // y = kx
    Lookup1D(float xP, float yP, float n); // y = kx
    float operator()(float x);
};


#endif //VCU_CORE_CURVEPARAMETER_H