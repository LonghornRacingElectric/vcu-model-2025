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
#include "blocks/BrakeLight.h"
#include "blocks/Stompp.h"
#include "blocks/TorqueMap.h"
#include "blocks/Cooling.h"
#include "blocks/ParkDriveSystem.h"

typedef struct VcuModelInputs {
    float apps1Voltage;
    float apps2Voltage;

    bool driveSwitchEnabled;
    bool tractiveSystemReady;
} VcuModelInputs;

typedef struct VcuModelOutputs {
    float torqueCommand;
    bool enableInverter;
    
    float apps1Percent;  // for observability
    float apps2Percent;  // for observability
    float appsPercent;  // for observability

    bool driveStateEnabled;
    float brakeLightPercent;
} VcuModelOutputs;

typedef struct VcuModelParameters {
    AppsParameters apps;

    STOMPPParameters stompp;
    TorqueMapParameters torque;
    CoolingParameters cooling;
    BrakeLightParameters brake_light;
} VcuModelParameters;


void VcuModel_evaluate(VcuModelInputs *inputs, VcuModelOutputs *outputs,
                       float deltaTime);

void VcuModel_setParams(VcuModelParameters *parameters);

#endif  // VCUMODEL_H
