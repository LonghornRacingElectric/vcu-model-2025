/*

Torque mappings from percentages and other datapoints to inverter torque request

Created by Dhairya on 2/28/2025

*/

#include "../util/Lookup1D.h"

#ifndef TORQUEMAP_H
#define TORQUEMAP_H

typedef struct TorqueMapInputs {
    float apps;            // pedal travel (%)
    float motorTemp;       // (deg C)
    float motorRpm;        // (rpm)
    float inverterTemp;    // (deg C)
    float batteryTemp;     // (deg C)
    float batterySoc;      // (%)
    float batteryVoltage;  // (V)
    float batteryCurrent;  // (A)
} TorqueMapInputs;

typedef struct TorqueMapOutputs {
    float torqueRequest;  // torque (Nm)
} TorqueMapOutputs;

typedef struct TorqueMapParameters {
    Lookup1D mapPedalToTorqueRequest;  // torque request (Nm) as a function of
                                       // pedal travel (%)
} TorqueMapParameters;


void TorqueMap_setParameters(TorqueMapParameters *params);

void TorqueMap_evaluate(TorqueMapInputs *inputs, TorqueMapOutputs *outputs);

#endif  // TORQUEMAP_H