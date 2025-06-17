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

typedef struct AppsInputs {
    float apps1Voltage;
    float apps2Voltage;
} AppsInputs;

typedef struct AppsOutputs {
    enum APPS_STATUS status;
    float appsPercent;
    float apps1Percent;
    float apps2Percent;
} AppsOutputs;

typedef struct AppsParameters {
    float apps1VoltageMin;
    float apps1VoltageMax;
    float apps2VoltageMin;
    float apps2VoltageMax;

    float appsMaxImplausibilityTime;
    float allowedPlausibilityRange;

    float appsDeadzoneBottomPercent;
    float appsDeadzoneTopPercent;
    float appsLowPassFilterTimeConstant;
} AppsParameters;


void AppsProcessor_setParams(AppsParameters *parameters);

void AppsProcessor_evaluate(AppsInputs *inputs, AppsOutputs *outputs,
                            float deltaTime);

#endif  // APPSPROCESSOR_H
