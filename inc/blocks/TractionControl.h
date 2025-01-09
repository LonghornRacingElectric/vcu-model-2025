//
// Created by henry on 1/7/2025.
//

#ifndef TRACTIONCONTROL_H
#define TRACTIONCONTROL_H

#include "VcuParameters.h"

#include "util/LowPassFilter.h"
// #include "util/Differentiator.h"


typedef struct TractionControlInput {
    float unregulatedTorqueRequest; // torque (Nm)

    float wheelSpeedFl; // (rad)
    float wheelSpeedFr;
    float wheelSpeedBl;
    float wheelSpeedBr;

    bool wheelSpeedsOk;
} TractionControlInput;


typedef struct TractionControlOutput {
    float regulatedTorqueRequest; // torque (Nm)
} TractionControlOutput;


class TractionControl {
private:
    //ask where are the differentiators used
    // Differentiator differentiatorFl;
    // Differentiator differentiatorFr;
    // Differentiator differentiatorBl;
    // Differentiator differentiatorBr;

    LowPassFilter lowPassFeedback = LowPassFilter(0);
public:
    void setParameters(VcuParameters* params);
    void evaluate(VcuParameters *params, TractionControlInput *input, TractionControlOutput *output, float deltaTime);
};

#endif //TRACTIONCONTROL_H
