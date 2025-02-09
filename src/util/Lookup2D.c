//
// Created by henry on 11/10/2024.
//


#include "../../inc/util/Lookup2D.h"
#include <cmath>
#include <cstring>

/**
 * Initialize surface as an 11x11 matrix.
 *
 * @param x0 minimum x, corresponds to first column, z[y][0]
 * @param x1 maximum x, corresponds to last column, z[y][10]
 * @param y0 minimum y, corresponds to first row, z[0][x]
 * @param y1 maximum y, corresponds to last row, z[10][x]
 * @param z 11x11 matrix of f(x, y) where row index corresponds to y and column index to x
 */
void Lookup2D_init(Lookup2D* lookup2d, float x0, float x1, float y0, float y1, float z[11][11]) {
    lookup2d->x0 = x0;
    lookup2d->x1 = x1;
    lookup2d->y0 = y0;
    lookup2d->y1 = y1;
    memcpy(lookup2d->z, z, sizeof(float) * 11 * 11);
}

float Lookup2D_evaluate(Lookup2D* lookup2d, float x, float y) {
    float xpct = (x - lookup2d->x0) / (lookup2d->x1 - lookup2d->x0) * 10.0f;
    xpct = fminf(xpct, 10.0f);
    xpct = fmaxf(xpct, 0.0f);

    int xi = (int) floorf(xpct);
    int xj = (int) ceilf(xpct);

    float ypct = (y - lookup2d->y0) / (lookup2d->y1 - lookup2d->y0) * 10.0f;
    ypct = fminf(ypct, 10.0f);
    ypct = fmaxf(ypct, 0.0f);

    int yi = (int) floorf(ypct);
    int yj = (int) ceilf(ypct);

    float a = xpct - (float) xi;
    float z0 = ((1-a) * lookup2d->z[yi][xi]) + (a * lookup2d->z[yi][xj]);
    float z1 = ((1-a) * lookup2d->z[yj][xi]) + (a * lookup2d->z[yj][xj]);

    float b = ypct - (float) yi;
    float zr = ((1-b) * z0) + (b * z1);

    return zr;
}

