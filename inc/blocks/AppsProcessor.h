/*

APPS Processor (Accelerator Pedal Pressure Sensors) -- To check rules compliance
on accelerator pedals

Created by Dhairya & Henry on 2/27/2025

*/

#ifndef APPSPROCESSOR_H
#define APPSPROCESSOR_H

#include <stdint.h>

#include "../VcuParameters.h"
#include "../util/Timer.h"

enum APPS_STATUS {
    APPS_OK = 0,           // 0x00
    APPS_DISAGREE = 1,     // 0x01
    APPS_OUT_OF_RANGE = 2  // 0x02
};

#define APPS_SHUTDOWN_MASK (APPS_DISAGREE)

typedef struct APPSInputs {
    float pedal1Voltage;
    float pedal2Voltage;
    float pedal1Percent;
    float pedal2Percent;
} APPSInputs;

typedef struct APPSOutputs {
    enum APPS_STATUS status;
    float pedalPercent;
} APPSOutputs;

typedef struct APPSParameters {
    float sensorInRangeUpperBound;   // G (NOT GEQ) is OUT OF BOUNDS
    float sensorInRangeLowerBound;   // L (NOT LEQ) IS OUT OF BOUNDS
    float allowedPlausibilityRange;  // ALLOWED TOLERANCE, INCLUSIVE
    float appsDeadzoneTopPercent;    // Percent pedal travel that isn't possible
    float appsDeadzoneBottomPercent;  // Percent pedal travel that isn't
                                      // possible from the bottom (0%)
    float appsMaxImplausibilityTime;  // max time the APPS can remain
                                      // implausible before fully implausible
    float pedal1Bias;  // how much to bias output percentage to pedal 1 vs 2
} APPSParameters;


void APPSProcessor_set_parameters(APPSParameters *parameters);

void APPSProcessor_evaluate(APPSInputs *inputs, APPSOutputs *outputs,
                            float deltaTime);

#endif  // APPSPROCESSOR_H
