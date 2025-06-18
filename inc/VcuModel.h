/*
 * Establishes inputs and evaluation for VCU Model
 *
 * Created by Dhairya & Henry on 2/26/2025
 */

#ifndef VCUMODEL_H
#define VCUMODEL_H

// include all the blocks and vcu params

#include "VcuParameters.h"
#include "blocks/AppsProcessor.h"
#include "blocks/BseProcessor.h"
#include "blocks/BrakeLight.h"
#include "blocks/Stompp.h"
#include "blocks/TorqueMap.h"
#include "blocks/ParkDriveSystem.h"

typedef struct VcuModelInputs {
    float apps1Voltage;
    float apps2Voltage;
    float bseFVoltage;
    float bseRVoltage;

    bool driveSwitchEnabled;
    bool tractiveSystemReady;
} VcuModelInputs;

typedef struct VcuModelOutputs {
    float torqueCommand;
    bool enableInverter;
    bool driveStateEnabled;
    bool buzzerEnabled;
    float brakeLightPercent;
    bool coolingOn;

    // observables
    enum APPS_STATUS appsStatus;
    float apps1Percent;
    float apps2Percent;
    float appsPercent;

    enum BSE_STATUS bseStatus;
    float bseFPressure;
    float bseRPressure;
    float bseAvgPressure;
    float bseAvgPercent;
    bool isDriverBraking;

    enum STOMPP_STATUS stomppStatus;
    float appsPercentStompp;

    float appsPercentSafe;
} VcuModelOutputs;

typedef struct VcuModelParameters {
    AppsParameters apps;
    BseParameters bse;
    StomppParameters stompp;
    // ParkDriveParameters parkDrive;
    TorqueMapParameters torque;

    // CoolingParameters cooling;
    // BrakeLightParameters brake_light;
} VcuModelParameters;


void VcuModel_evaluate(VcuModelInputs *inputs, VcuModelOutputs *outputs,
                       float deltaTime);

void VcuModel_setParams(VcuModelParameters *parameters);

#endif  // VCUMODEL_H
