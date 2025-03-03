#include "../../inc/blocks/BrakeLight.h"

#include "../../inc/util/LowPassFilter.h"

static BrakeLightParameters brake_light_params;

static LowPassFilter brake_filter;

void BrakeLight_setParameters(BrakeLightParameters* params) {
    brake_light_params = *params;

    LowPassFilter_init(&brake_filter, params->bseTimeConstant);
}

void BrakeLight_evaluate(BrakeLightInputs* inputs, BrakeLightOutputs* outputs,
                         float deltaTime) {
    LowPassFilter_add(&brake_filter, inputs->bsePercent, deltaTime);

    float bsePercent = LowPassFilter_get(&brake_filter);

    outputs->lightOn = bsePercent >= brake_light_params.bseLightOnPercent;
}