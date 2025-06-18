/*

APPS Processor (Accelerator Pedal Pressure Sensors) -- To check rules compliance
on accelerator pedals

Created by Dhairya & Henry on 2/27/2025

*/

#ifndef BSEPROCESSOR_H
#define BSEPROCESSOR_H

#include <stdint.h>

#include "../VcuParameters.h"
#include "../util/Timer.h"

enum BSE_STATUS {
    BSE_OK = 0,           // 0x00
    BSE_OUT_OF_RANGE = 1  // 0x01
};

typedef struct BseInputs {
    float bseFVoltage;
    float bseRVoltage;
    // TODO BSE3
} BseInputs;

typedef struct BseOutputs {
    enum BSE_STATUS status;
    float bseFPressure;
    float bseRPressure;
    float bseAvgPressure;
    float bseAvgPercent;
    bool isDriverBraking;
} BseOutputs;

typedef struct BseParameters {
    float bseMinAllowableVoltage;
    float bseMaxAllowableVoltage;

    float bseZeroPressureVoltage;
    float bseMaxPressureVoltage;
    float bseMaxPressure;

    float bseBrakingPressure;

    float bseMaxImplausibilityTime;
    float bseLowPassFilterTimeConstant;
} BseParameters;


void BseProcessor_setParams(BseParameters *parameters);

void BseProcessor_evaluate(BseInputs *inputs, BseOutputs *outputs,
                            float deltaTime);

#endif  // APPSPROCESSOR_H
