////
//// Created by henry on 10/27/2024.
////
//
#ifndef BRAKELIGHT_H
#define BRAKELIGHT_H

#include <stdbool.h>

#include "../util/LowPassFilter.h"

typedef struct BrakeLightParameters {
    float bseLightOnPercent;
    float bseTimeConstant;
} BrakeLightParameters;

typedef struct BrakeLightInputs {
    float bsePercent;
} BrakeLightInputs;

typedef struct BrakeLightOutputs {
    bool lightOn;
} BrakeLightOutputs;

static BrakeLightParameters brake_light_params;

static LowPassFilter brake_filter;

void BrakeLight_setParameters(BrakeLightParameters* params);

void BrakeLight_evaluate(BrakeLightInputs* inputs, BrakeLightOutputs* outputs,
                         float deltaTime);

#endif  // BRAKELIGHT_H
