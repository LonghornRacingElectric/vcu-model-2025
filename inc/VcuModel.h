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
    // STOMPP Inputs
    STOMPPInputs stompp;
    APPSParameters apps;
} VCUModelInputs;

typedef struct VCUModelParameters {
    STOMPPParameters stompp;
    APPSParameters apps;
    VcuParameters vcu;
} VCUModelParameters;

#endif  // VCUMODEL_H
