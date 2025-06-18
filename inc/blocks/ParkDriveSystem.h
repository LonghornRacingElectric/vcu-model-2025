//
// Created by Dhairya Gupta on 6/15/25.
//

#ifndef VCU_FIRMWARE_2025_PARKDRIVESYSTEM_H
#define VCU_FIRMWARE_2025_PARKDRIVESYSTEM_H

#include "VcuModel.h"

typedef struct ParkDriveInputs
{
  float appsPercent;
  float appsPercentStompp;
  bool isDriverBraking;
  bool driveSwitchEnabled;
  bool tractiveSystemReady;
} ParkDriveInputs;

typedef struct ParkDriveOutputs
{
  bool driveStateEnabled;
  bool buzzerEnabled;
  float appsPercentSafe;
} ParkDriveOutputs;

typedef struct ParkDriveParameters
{
  float buzzerDuration;
} ParkDriveParameters;

void ParkDriveSystem_setParams();
void ParkDriveSystem_evaluate(ParkDriveInputs *inputs, ParkDriveOutputs *outputs, float deltaTime);

#endif //VCU_FIRMWARE_2025_PARKDRIVESYSTEM_H
