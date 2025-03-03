//
// Created by henry on 1/7/2025.
//

#include "../../inc/util/LowPassFilter.h"

void LowPassFilter_init(LowPassFilter* lowpass, float timeConstant) {
    lowpass->timeConstant = timeConstant;
    lowpass->accumulator = 0;
}

void LowPassFilter_reset(LowPassFilter* lowpass) {
    lowpass->accumulator = 0;
}

void LowPassFilter_add(LowPassFilter* lowpass, float value, float deltaTime) {
    float alpha = deltaTime / (lowpass->timeConstant + deltaTime);
    lowpass->accumulator = (lowpass->accumulator * (1-alpha)) + (value * alpha);
}

float LowPassFilter_get(LowPassFilter* lowpass) {
    return lowpass->accumulator;
}
