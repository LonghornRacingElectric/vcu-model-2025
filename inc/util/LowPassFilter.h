//
// Created by henry on 1/7/2025.
//

#ifndef LOWPASSFILTER_H
#define LOWPASSFILTER_H

/**
 * Digital Low Pass Filter:
 * http://techteach.no/simview/lowpass_filter/doc/filter_algorithm.pdf
 */
typedef struct LowPassFilter {
    float timeConstant;
    float accumulator;
} LowPassFilter;

void LowPassFilter_init(LowPassFilter* lowpass, float timeConstant);
void LowPassFilter_add(LowPassFilter* lowpass, float value, float deltaTime);
float LowPassFilter_get(LowPassFilter* lowpass);
void LowPassFilter_reset(LowPassFilter* lowpass);

#endif  // LOWPASSFILTER_H
