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



  outputs->apps1Percent = appsOutputs.apps1Percent;
  outputs->apps2Percent = appsOutputs.apps2Percent;
  outputs->appsPercent = appsOutputs.appsPercent;


  // ParkDriveSystem_evaluate(&inputs->stompp, &outputs->stompp, inputs->drive_switch_enabled,
  //                          inputs->tractive_system_active, deltaTime);
  //
  // // pass the APPS output into STOMPP
  // inputs->stompp.apps_percent = outputs->apps.pedalPercent;
  //
  // STOMPP_evaluate(&inputs->stompp, &outputs->stompp);
  //
  // if (outputs->stompp.output != STOMPP_OK) {
  //     outputs->apps.pedalPercent = 0.0f;
  // }
  //
  // Cooling_batt_evaluate(&inputs->cooling, &outputs->cooling);
  // Cooling_motor_evaluate(&inputs->cooling, &outputs->cooling);
  // inputs->torque.apps = outputs->apps.pedalPercent;
  // TorqueMap_evaluate(&inputs->torque, &outputs->torque);
  // BrakeLight_evaluate(&inputs->brake_light, &outputs->brake_light, deltaTime);
}
