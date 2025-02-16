
#include "../../inc/util/Lookup1D.h"
//#include <cmath>
#include "math.h"
#include <string.h>
//#include <iostream>



void Lookup1D_init(Lookup1D* lookup1d, float xP, float yP) {
    lookup1d->x0 = 0.0f;
    lookup1d->x1 = xP;
    for(int i = 0; i < 11; i++) {
        lookup1d->y[i] = yP * ((float)i) / 10.0f;
    }
}
// void Lookup1D_print(Lookup1D* lookup1d) {
//     for(int i = 0; i < 11; i++) {
//         std::cout << lookup1d->y[i] << std::endl;
//     }
// }

float Lookup1D_evaluate(Lookup1D* lookup1d, float x) {
    float pct = (x - lookup1d->x0) / (lookup1d->x1 - lookup1d->x0) * 10.0f;
    pct = fminf(pct, 10.0f);
    pct = fmaxf(pct, 0.0f);

    int i = (int) floorf(pct);
    int j = (int) ceilf(pct);

    float a = pct - (float) i;
    float yr = ((1-a) * lookup1d->y[i]) + (a * lookup1d->y[j]);
    return yr;
}
