//
// Created by henry on 10/27/2024.
//

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
} VCUModelInputs;

typedef struct VCUModelParameters {
    STOMPPParameters stompp;
    VcuParameters vcu;
} VCUModelParameters;

#endif  // VCUMODEL_H
