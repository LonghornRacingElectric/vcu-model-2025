
#include "../../inc/util/Lookup1D.h"
#include <cmath>
#include <cstring>

Lookup1D::Lookup1D(float x0, float x1, float y[], float n) {
    this->x0 = x0;
    this->x1 = x1;
    memcpy(this->y, y, sizeof(float) * (n+1));
}

Lookup1D::Lookup1D(float xP, float yP) {
    this->x0 = 0.0f;
    this->x1 = xP;
    this->n = 10.0;
    for(int i = 0; i < 11; i++) {
        this->y[i] = yP * ((float)i) / this->n;
    }
}
Lookup1D::Lookup1D(float xP, float yP, float n) {
    this->x0 = 0.0f;
    this->x1 = xP;
    this->n = n;
    for(int i = 0; i < 11; i++) {
        this->y[i] = yP * ((float)i) / this->n;
    }
}

float Lookup1D::operator()(float x) {
    float pct = (x - x0) / (x1 - x0) * 10.0f;
    pct = fminf(pct, 10.0f);
    pct = fmaxf(pct, 0.0f);

    int i = (int) floorf(pct);
    int j = (int) ceilf(pct);

    float a = pct - (float) i;
    float yr = ((1-a) * y[i]) + (a * y[j]);
    return yr;
}
