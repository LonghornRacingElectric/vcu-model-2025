//
// Created by henry on 1/8/2025.
//

#ifndef COOLING_H
#define COOLING_H



#include "VcuParameters.h"


typedef struct CoolingInput {
    float batteryTemp;
    float inverterTemp;
    float motorTemp;
} CoolingInput;


typedef struct CoolingOutput {
    float pumpOutput;
    float radiatorOutput;
    float batteryFansOutput;
} CoolingOutput;


class Cooling {
public:
    void setParameters(VcuParameters* params);
    void evaluate(VcuParameters *params, CoolingInput *input, CoolingOutput *output, float deltaTime);
};
#endif //COOLING_H
