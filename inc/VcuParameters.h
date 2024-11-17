//
// Created by henry on 10/27/2024.
//

#ifndef VCUPARAMETERS_H
#define VCUPARAMETERS_H

//#include "../util/CurveParameter.h"

#include "util/Lookup1D.h"

typedef struct VcuParameters {
    //APPS PARAMAETERS
    float appsPlausibilityRange = 0.10f; //(%)
    float appsDeadZoneBottomPct = 0.08f; // (%) of travel that is 0 or 100
    float appsDeadZoneTopPct = 0.13f; // (%) of travel that is 0 or 100

    // BRAKE PARAMETERS
    float brakesSoftThreshold = 0.03f; // minimum brakes to count as mechanical brakes engaged for EV 4.7, also brake light (%)
    float brakesHardThreshold = 0.08f; // hard braking (%)

    //STOMPP
    float stomppAppsCutoffThreshold = 0.25f; // apps pedal travel where motor power needs to be cut off (%)
    float stomppAppsRecoveryThreshold = 0.05f; // apps pedal travel where motor power can be restored (%)
    //TORQUE MAP
    Lookup1D mapPedalToTorqueRequest = Lookup1D(1.0f,
                                                         230.0f); // torque request (Nm) as a function of pedal travel (%)
}VcuParameters;

#endif //VCUPARAMETERS_H
