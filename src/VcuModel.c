/*
 * Establishes inputs and evaluation for VCU Model
 *
 * Created by Dhairya & Henry on 2/26/2025
 */

#include "../inc/VcuModel.h"

void VCUModel_set_parameters(VCUModelParameters* parameters) {
    model_parameters = *parameters;

    APPSProcessor_set_parameters(&parameters->apps);
    STOMPP_set_parameters(&parameters->stompp);
}

void VCUModel_evaluate(VCUModelInputs* inputs, VCUModelOutputs* outputs,
                       float deltaTime) {
    APPSProcessor_evaluate(&inputs->apps, &outputs->apps, deltaTime);

    // TODO make sure drive switch is enabled before doing this

    // pass the APPS output into STOMPP
    inputs->stompp.apps_percent = outputs->apps.pedalPercent;

    STOMPP_evaluate(&inputs->stompp, &outputs->stompp);

    TorqueMap_evaluate(&inputs->torque, &outputs->torque);
}