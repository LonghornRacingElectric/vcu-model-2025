//
// Created by henry on 1/7/2025.
//

#ifndef TRACTIONCONTROL_H
#define TRACTIONCONTROL_H

#include <stdbool.h>

#include "../VcuParameters.h"
#include "../util/LowPassFilter.h"

typedef struct TractionControlInput {
    float unregulatedTorqueRequest;  // torque (Nm)

    float wheelSpeedFl;  // (rad)
    float wheelSpeedFr;
    float wheelSpeedBl;
    float wheelSpeedBr;

    bool wheelSpeedsOk;
} TractionControlInput;

typedef struct TractionControlOutput {
    float regulatedTorqueRequest;  // torque (Nm)
} TractionControlOutput;

typedef struct TractionControl {
    LowPassFilter lowPassFeedback;
} TractionControl;

void setParameters(TractionControl* tractionControl, VcuParameters* params);
void evaluate(TractionControl* tractionControl, VcuParameters* params,
              TractionControlInput* input, TractionControlOutput* output,
              float deltaTime);

#endif  // TRACTIONCONTROL_H
