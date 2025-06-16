//
// Created by Dhairya Gupta on 6/15/25.
//

#ifndef VCU_FIRMWARE_2025_PARKDRIVESYSTEM_H
#define VCU_FIRMWARE_2025_PARKDRIVESYSTEM_H

#include "VcuModel.h"

void ParkDriveSystem_set_parameters(STOMPPParameters *parameters);
void ParkDriveSystem_evaluate(STOMPPInputs *inputs, STOMPPOutputs *outputs, bool drive_switch_enabled,
                              bool tractive_system_active, float dt);
#endif //VCU_FIRMWARE_2025_PARKDRIVESYSTEM_H
