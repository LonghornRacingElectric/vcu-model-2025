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

typedef struct VCUModelInputs {
    APPSInputs apps;
    STOMPPInputs stompp;
    TorqueMapInputs torque;
    CoolingInputs cooling;
    BrakeLightInputs brake_light;
} VCUModelInputs;

typedef struct VCUModelOutputs {
    APPSOutputs apps;
    STOMPPOutputs stompp;
    TorqueMapOutputs torque;
    CoolingOutputs cooling;
    BrakeLightOutputs brake_light;

} VCUModelOutputs;

typedef struct VCUModelParameters {
    APPSParameters apps;
    STOMPPParameters stompp;
    TorqueMapParameters torque;
    CoolingParameters cooling;

    BrakeLightParameters brake_light;
} VCUModelParameters;


void VCUModel_evaluate(VCUModelInputs *inputs, VCUModelOutputs *outputs,
                       float deltaTime);

void VCUModel_set_parameters(VCUModelParameters *parameters);

#endif  // VCUMODEL_H
