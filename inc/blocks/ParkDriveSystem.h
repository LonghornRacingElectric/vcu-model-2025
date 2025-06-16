//
// Created by Dhairya Gupta on 6/15/25.
//

#ifndef VCU_FIRMWARE_2025_PARKDRIVESYSTEM_H
#define VCU_FIRMWARE_2025_PARKDRIVESYSTEM_H

#include "VcuModel.h"

void ParkDriveSystem_set_parameters(VCUModelParameters *parameters);
void ParkDriveSystem_evaluate(VCUModelInputs *inputs, VCUModelOutputs *outputs, float dt);

#endif //VCU_FIRMWARE_2025_PARKDRIVESYSTEM_H
