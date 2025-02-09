//
// Created by henry on 10/27/2024.
//

#ifndef VCUPARAMETERS_H
#define VCUPARAMETERS_H

//#include "../util/CurveParameter.h"

#include "../inc/util/Lookup1D.h"
#include <stdbool.h>

// typedef struct VcuParameters {
//     //APPS PARAMAETERS
//     float appsPlausibilityRange = 0.10f; //(%)
//     float appsDeadZoneBottomPct = 0.08f; // (%) of travel that is 0 or 100
//     float appsDeadZoneTopPct = 0.13f; // (%) of travel that is 0 or 100
//     float appsImplausibilityTime = 0.100f; // (s)
//
//     // BRAKE PARAMETERS
//     float brakesSoftThreshold = 0.03f; // minimum brakes to count as mechanical brakes engaged for EV 4.7, also brake light (%)
//     float brakesHardThreshold = 0.08f; // hard braking (%)
//
//     // ===== PRNDL PARAMETERS =====
//     float prndlBrakeToStartThreshold = 0.1f; // minimum brakes required to go into drive (%)
//     float prndlBuzzerDuration = 2.0f; // how long the buzzer buzzes (s)
//     float prndlSwitchDebounceDuration = 0.100f; // how long a digital high/low must be sustained to be considered (s)
//
//     //STOMPP
//     float stomppAppsCutoffThreshold = 0.25f; // apps pedal travel where motor power needs to be cut off (%)
//     float stomppAppsRecoveryThreshold = 0.05f; // apps pedal travel where motor power can be restored (%)
//     float stomppMechanicalBrakesThreshold = 0.1f;
//
//     // ==== TRACTION CONTROL PARAMETERS =====
//     bool tcsEnabled = false;
//     float tcsFeedbackLowPassFilterTimeConstant = 0.050f;
//
//     // ==== STEERING PARAMETERS ====
//     Lookup1D steeringWheelToOuterWheel;
//     Lookup1D steeringWheelToInnerWheel;
//     float steeringPotMaxVoltage = 3.3f;
//     float steeringWheelMaxAngle = 120.0f;
//
//     // ==== COOLING PARAMETERS =====
//     Lookup1D  coolingBattery;
//     Lookup1D  coolingMotor;
//
//
//     //TORQUE MAP
//     Lookup1D mapPedalToTorqueRequest; // torque request (Nm) as a function of pedal travel (%)
// }VcuParameters;

typedef struct VcuParameters {
    //APPS PARAMAETERS
    float appsPlausibilityRange; //(%)
    float appsDeadZoneBottomPctf; // (%) of travel that is 0 or 100
    float appsDeadZoneTopPct; // (%) of travel that is 0 or 100
    float appsImplausibilityTime; // (s)

    // BRAKE PARAMETERS
    float brakesSoftThreshold; // minimum brakes to count as mechanical brakes engaged for EV 4.7, also brake light (%)
    float brakesHardThreshold; // hard braking (%)

    // ===== PRNDL PARAMETERS =====
    float prndlBrakeToStartThreshold; // minimum brakes required to go into drive (%)
    float prndlBuzzerDuration; // how long the buzzer buzzes (s)
    float prndlSwitchDebounceDuration; // how long a digital high/low must be sustained to be considered (s)

    //STOMPP
    float stomppAppsCutoffThreshold; // apps pedal travel where motor power needs to be cut off (%)
    float stomppAppsRecoveryThreshold; // apps pedal travel where motor power can be restored (%)
    float stomppMechanicalBrakesThreshold;

    // ==== TRACTION CONTROL PARAMETERS =====
    bool tcsEnabled;
    float tcsFeedbackLowPassFilterTimeConstant;

    // ==== STEERING PARAMETERS ====
    Lookup1D steeringWheelToOuterWheel;
    Lookup1D steeringWheelToInnerWheel;
    float steeringPotMaxVoltage;
    float steeringWheelMaxAngle;

    // ==== COOLING PARAMETERS =====
    Lookup1D  coolingBattery;
    Lookup1D  coolingMotor;


    //TORQUE MAP
    Lookup1D mapPedalToTorqueRequest; // torque request (Nm) as a function of pedal travel (%)
}VcuParameters;

#endif //VCUPARAMETERS_H
