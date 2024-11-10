//
// Created by henry on 10/27/2024.
//

#ifndef BREAKLIGHT_H
#define BREAKLIGHT_H

#include "../src/VcuParameters.h"

typedef struct BreakLightInput {
    //bool parkOrDrive; implement later
    float bse; //break (%)
}BreakLightInput;

typedef struct BreakLightOutput {
    float brakeLight;
}BreakLightOutput;

class BreakLight {
private:
    float brakeTimer = 0;
    float accumulator = 0;
    float time = 0;
public:
    void setParameters(VcuParameters* params);
    void evaluate(VcuParameters *params, BreakLightInput *input, BreakLightOutput *output, float deltaTime);
};



#endif //BREAKLIGHT_H
