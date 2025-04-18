#include "../../inc/util/Lookup2D.h"

#include <math.h>    // For floorf, ceilf, fminf, fmaxf
#include <stdio.h>   // For printf in Lookup2D_print
#include <string.h>  // For memcpy

// accessoble segments
#define LOOKUP2D_SEGMENTS_X (LOOKUP2D_POINTS_X - 1)
#define LOOKUP2D_SEGMENTS_Y (LOOKUP2D_POINTS_Y - 1)

void Lookup2D_init(Lookup2D* lookup2d, float x0, float x1, float y0, float y1,
                   const float z_data[LOOKUP2D_POINTS_Y][LOOKUP2D_POINTS_X]) {
    if (!lookup2d) {
        return;  // Handle null pointer
    }

    lookup2d->x0 = x0;
    lookup2d->x1 = x1;
    lookup2d->y0 = y0;
    lookup2d->y1 = y1;

    // Ensure ranges are valid (min <= max) to avoid division by zero later
    if (lookup2d->x1 <= lookup2d->x0) {
        lookup2d->x1 = lookup2d->x0 + 1.0f;  // Assign a default valid range
    }
    if (lookup2d->y1 <= lookup2d->y0) {
        lookup2d->y1 = lookup2d->y0 + 1.0f;  // Assign a default valid range
    }

    // Copy lookup table
    if (z_data) {
        memcpy(lookup2d->z, z_data, sizeof(lookup2d->z));
    } else {
        // if null, just in case, we'll make sure everything 0 so we don't risk
        // anything
        memset(lookup2d->z, 0, sizeof(lookup2d->z));
    }
}

float Lookup2D_evaluate(const Lookup2D* lookup2d, float x, float y) {
    if (!lookup2d) {
        // Handle null pointer - return a default value or NaN?
        return 0.0f;  // Or NAN if using <math.h> extensively
    }

    // Calculate normalized position within the grid [0, LOOKUP2D_SEGMENTS_X/Y]
    float pct_x = (x - lookup2d->x0) / (lookup2d->x1 - lookup2d->x0) *
                  (float)LOOKUP2D_SEGMENTS_X;
    float pct_y = (y - lookup2d->y0) / (lookup2d->y1 - lookup2d->y0) *
                  (float)LOOKUP2D_SEGMENTS_Y;

    // Clamp normalized positions to the valid range [0, LOOKUP2D_SEGMENTS_X/Y]
    // This handles inputs outside the x0-x1 and y0-y1 range.
    pct_x = fmaxf(0.0f, fminf(pct_x, (float)LOOKUP2D_SEGMENTS_X));
    pct_y = fmaxf(0.0f, fminf(pct_y, (float)LOOKUP2D_SEGMENTS_Y));

    // Find integer indices of the surrounding grid points
    int ix0 = (int)floorf(pct_x);
    int ix1 = (int)ceilf(pct_x);
    int iy0 = (int)floorf(pct_y);
    int iy1 = (int)ceilf(pct_y);

    // Clamp indices just in case of floating point edge cases near the max
    // boundary Although clamping pct_* should make this redundant, it adds
    // robustness.
    ix0 = fmaxf(0, fminf(ix0, LOOKUP2D_SEGMENTS_X));
    ix1 = fmaxf(0, fminf(ix1, LOOKUP2D_SEGMENTS_X));
    iy0 = fmaxf(0, fminf(iy0, LOOKUP2D_SEGMENTS_Y));
    iy1 = fmaxf(0, fminf(iy1, LOOKUP2D_SEGMENTS_Y));

    // Get the four corner Z values from the table
    // z[row][column] -> z[y_index][x_index]
    float z00 = lookup2d->z[iy0][ix0];  // Z at (x0_idx, y0_idx)
    float z01 = lookup2d->z[iy0][ix1];  // Z at (x1_idx, y0_idx)
    float z10 = lookup2d->z[iy1][ix0];  // Z at (x0_idx, y1_idx)
    float z11 = lookup2d->z[iy1][ix1];  // Z at (x1_idx, y1_idx)

    // Calculate interpolation factors (weights) [0, 1]
    float ax = pct_x - (float)ix0;  // Weight for interpolation along X
    float ay = pct_y - (float)iy0;  // Weight for interpolation along Y

    // Interpolate along X-axis for lower y-index (y = iy0)
    float z_interp_y0 = (1.0f - ax) * z00 + ax * z01;

    // Interpolate along X-axis for upper y-index (y = iy1)
    float z_interp_y1 = (1.0f - ax) * z10 + ax * z11;

    // Interpolate along Y-axis between the two intermediate results
    float final_z = (1.0f - ay) * z_interp_y0 + ay * z_interp_y1;

    return final_z;
}