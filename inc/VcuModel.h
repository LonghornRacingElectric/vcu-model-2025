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

typedef struct VCUModelInputs {
    APPSInputs apps;
    STOMPPInputs stompp;
    TorqueMapInputs torque;

    BrakeLightInputs brake_light;
} VCUModelInputs;

typedef struct VCUModelOutputs {
    APPSOutputs apps;
    STOMPPOutputs stompp;
    TorqueMapOutputs torque;

    BrakeLightOutputs brake_light;

} VCUModelOutputs;

typedef struct VCUModelParameters {
    APPSParameters apps;
    STOMPPParameters stompp;
    TorqueMapParameters torque;

    BrakeLightParameters brake_light;
} VCUModelParameters;

static VCUModelParameters model_parameters;

void VCUModel_evaluate(VCUModelInputs *inputs, VCUModelOutputs *outputs,
                       float deltaTime);

void VCUModel_set_parameters(VCUModelParameters *parameters);

#endif  // VCUMODEL_H
