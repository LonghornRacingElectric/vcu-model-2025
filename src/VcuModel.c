/*
 * Establishes inputs and evaluation for VCU Model
 *
 * Created by Dhairya & Henry on 2/26/2025
 */

#include "../inc/VcuModel.h"

static VCUModelParameters model_parameters;

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

    if (outputs->stompp.output != STOMPP_OK) {
        outputs->apps.pedalPercent = 0.0f;
    }

    TorqueMap_evaluate(&inputs->torque, &outputs->torque);

    BrakeLight_evaluate(&inputs->brake_light, &outputs->brake_light, deltaTime);
}