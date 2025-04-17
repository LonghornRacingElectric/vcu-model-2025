#ifndef VCU_CORE_Lookup2D_H
#define VCU_CORE_Lookup2D_H

// Size of the lookups
#define LOOKUP2D_POINTS_X 11
#define LOOKUP2D_POINTS_Y 11

typedef struct Lookup2D {
    float x0;  // Minimum value of the X-axis input
    float x1;  // Maximum value of the X-axis input
    float y0;  // Minimum value of the Y-axis input
    float y1;  // Maximum value of the Y-axis input

    float z[LOOKUP2D_POINTS_Y][LOOKUP2D_POINTS_X];
} Lookup2D;

/**
 * @brief Initializes a 2D lookup table structure.
 *
 * @param lookup2d Pointer to the Lookup2D structure to initialize.
 * @param x0 The minimum value of the X-axis input range.
 * @param x1 The maximum value of the X-axis input range.
 * @param y0 The minimum value of the Y-axis input range.
 * @param y1 The maximum value of the Y-axis input range.
 * @param z_data A 2D array [LOOKUP2D_POINTS_Y][LOOKUP2D_POINTS_X]
 * containing the output (z) values for the grid points.
 * z_data[0][0] corresponds to input (x0, y0).
 * z_data[LOOKUP2D_POINTS_Y-1][LOOKUP2D_POINTS_X-1] corresponds to input (x1,
 * y1). The data is copied into the lookup2d structure.
 */
void Lookup2D_init(Lookup2D* lookup2d, float x0, float x1, float y0, float y1,
                   const float z_data[LOOKUP2D_POINTS_Y][LOOKUP2D_POINTS_X]);

/**
 * @brief Evaluates the 2D lookup table for given x and y inputs using bilinear
 * interpolation.
 *
 * Inputs outside the defined [x0, x1] and [y0, y1] ranges will be clamped to
 * the boundaries.
 *
 * @param lookup2d Pointer to the initialized Lookup2D structure.
 * @param x The input value for the X-axis.
 * @param y The input value for the Y-axis.
 * @return The interpolated output (z) value.
 */
float Lookup2D_evaluate(const Lookup2D* lookup2d, float x, float y);

#endif  // VCU_CORE_Lookup2D_H