/*

Torque mappings from percentages and other datapoints to inverter torque request

Created by Dhairya on 2/28/2025

*/

#include <stdbool.h>

#include "../util/Lookup1D.h"

#ifndef TORQUEMAP_H
#define TORQUEMAP_H

typedef struct TorqueMapInputs {
    float appsPercentSafe; // pedal travel (%)
    bool appsOk, bseOk, stomppOk, driveStateEnabled;

    float motorTemp;       // (deg C)
    float inverterTemp;    // (deg C)
    float batteryTemp;     // (deg C)
    float batterySoc;      // (%)
} TorqueMapInputs;

typedef struct TorqueMapOutputs {
    float torqueCommand;  // torque (Nm)
    bool enableInverter;// TODO move to last step
} TorqueMapOutputs;

typedef struct TorqueMapParameters {
    Lookup1D mapPedalToTorqueRequest;  // torque request (Nm) as a function of
                                       // pedal travel (%)
} TorqueMapParameters;


void TorqueMap_setParameters(TorqueMapParameters *params);

void TorqueMap_evaluate(TorqueMapInputs *inputs, TorqueMapOutputs *outputs, float deltaTime);

#endif  // TORQUEMAP_H