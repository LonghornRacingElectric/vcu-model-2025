/*
 * Establishes inputs and evaluation for VCU Model
 *
 * Created by Dhairya & Henry on 2/26/2025
 */

#include "../inc/VcuModel.h"

static VcuModelParameters vcuParams;

void VcuModel_setParams(VcuModelParameters* parameters)
{
  vcuParams = *parameters;
  AppsProcessor_setParams(&vcuParams.apps);

  // STOMPP_set_parameters(&parameters->stompp);
  // TorqueMap_setParameters(&parameters->torque);
  // Cooling_setParameters(&parameters->cooling);
  // ParkDriveSystem_set_parameters(&parameters->stompp);
}

void VcuModel_evaluate(VcuModelInputs* inputs, VcuModelOutputs* outputs,
                       float deltaTime)
{
  AppsInputs appsInputs = {
    inputs->apps1Voltage,
    inputs->apps2Voltage,
  };
  AppsOutputs appsOutputs = {};
  AppsProcessor_evaluate(&appsInputs, &appsOutputs, deltaTime);

  BseInputs bseInputs = {
    inputs->bseFVoltage,
    inputs->bseRVoltage,
  };
  BseOutputs bseOutputs = {};
  BseProcessor_evaluate(&bseInputs, &bseOutputs, deltaTime);

  StomppInputs stomppInputs = {
    .appsPercent = appsOutputs.appsPercent,
    .isDriverBraking = bseOutputs.isDriverBraking
  };
  StomppOutputs stomppOutputs = {};
  Stompp_evaluate(&stomppInputs, &stomppOutputs, deltaTime);

  ParkDriveInputs parkDriveInputs = {
    .appsPercent = appsOutputs.appsPercent,
    .appsPercentStompp = stomppOutputs.appsPercentStompp,
    .isDriverBraking = bseOutputs.isDriverBraking,
    .driveSwitchEnabled = inputs->driveSwitchEnabled,
  };
  ParkDriveOutputs parkDriveOutputs = {};
  ParkDriveSystem_evaluate(&parkDriveInputs, &parkDriveOutputs, deltaTime);

  TorqueMapInputs torqueMapInputs = {
    .appsPercentSafe = parkDriveOutputs.appsPercentSafe,
    .appsOk = !appsOutputs.status,
    .bseOk = !bseOutputs.status,
    .stomppOk = !stomppOutputs.status,
    .driveStateEnabled = parkDriveOutputs.driveStateEnabled,
    .motorTemp = 0,
    .inverterTemp = 0,
    .batteryTemp = 0,
    .batterySoc = 0,
  };
  TorqueMapOutputs torqueMapOutputs = {};
  TorqueMap_evaluate(&torqueMapInputs, &torqueMapOutputs, deltaTime);

  // TODO brake light system
  outputs->brakeLightPercent = (bseOutputs.isDriverBraking) ? 0.020f : 0.002f;
  // TODO cooling lmao
  outputs->coolingOn = parkDriveOutputs.driveStateEnabled;

  outputs->appsStatus = appsOutputs.status;
  outputs->apps1Percent = appsOutputs.apps1Percent;
  outputs->apps2Percent = appsOutputs.apps2Percent;
  outputs->appsPercent = appsOutputs.appsPercent;

  outputs->bseStatus = bseOutputs.status;
  outputs->bseFPressure = bseOutputs.bseFPressure;
  outputs->bseRPressure = bseOutputs.bseRPressure;
  outputs->bseAvgPercent = bseOutputs.bseAvgPressure;
  outputs->bseAvgPercent = bseOutputs.bseAvgPercent;
  outputs->isDriverBraking = bseOutputs.isDriverBraking;

  outputs->stomppStatus = stomppOutputs.status;
  outputs->appsPercentStompp = stomppOutputs.appsPercentStompp;

  outputs->driveStateEnabled = parkDriveOutputs.driveStateEnabled;
  outputs->buzzerEnabled = parkDriveOutputs.buzzerEnabled;
  outputs->appsPercentSafe = parkDriveOutputs.appsPercentSafe;


  // Cooling_batt_evaluate(&inputs->cooling, &outputs->cooling);
  // Cooling_motor_evaluate(&inputs->cooling, &outputs->cooling);
  // inputs->torque.apps = outputs->apps.pedalPercent;
  // TorqueMap_evaluate(&inputs->torque, &outputs->torque);
  // BrakeLight_evaluate(&inputs->brake_light, &outputs->brake_light, deltaTime);
}
