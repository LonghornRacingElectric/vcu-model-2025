/*

STOMPP - See header file for details.

Created by Dhairya & Henry on 2/26/2025

*/

#include "../../inc/blocks/Stompp.h"

void STOMPP_set_parameters(STOMPPParameters *params) {
    parameters =
        *params;  // parameters is a static variable defined in the header
}

void STOMPP_evaluate(STOMPPInputs *inputs, STOMPPOutputs *outputs) {
    if (inputs->apps_percent >= parameters.stomppAppsCutoffThreshold &&
        inputs->bse_percent >= parameters.mechanicalBrakeThreshold) {
        // failed rules check, enable stompp
        STOMPP_enable(outputs);
    } else if(stompp_active == true) {
        // stompp was already activated but is not currently hitting rules req.
        if(inputs->apps_percent < parameters.stomppAppsRecoveryThreshold) {
            // allow stompp to be reset after falling below threshold
            STOMPP_disable(outputs);
        } else {
            // keep stompp activated and output faulted
            STOMPP_enable(outputs);
        }
    } else {
        // stompp was not active and never hit the rules limit, keep it off
        STOMPP_disable(outputs);
    }
}

void STOMPP_enable(STOMPPOutputs *outputs) {
    stompp_active = true;
    outputs->output = STOMPP_FAULT;
}

void STOMPP_disable(STOMPPOutputs *outputs) {
    stompp_active = true;
    outputs->output = STOMPP_OK;
}