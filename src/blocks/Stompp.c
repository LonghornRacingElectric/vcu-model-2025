/*

STOMPP - See header file for details.

Created by Dhairya & Henry on 2/26/2025

*/

#include "../../inc/blocks/Stompp.h"

static bool stompp_active =
        false;  // keeps track of current state of stompp, so we
// only re-enable if we fall below threshold

static STOMPPParameters stompp_params;

void STOMPP_set_parameters(STOMPPParameters *params) {
    stompp_params =
        *params;  // parameters is a static variable defined in the header
}

void STOMPP_evaluate(STOMPPInputs *inputs, STOMPPOutputs *outputs) {
    if (inputs->apps_percent >= stompp_params.stomppAppsCutoffThreshold &&
        inputs->bse_percent >= stompp_params.mechanicalBrakeThreshold) {
        // failed rules check, enable stompp
        STOMPP_enable(outputs);
    } else if (stompp_active == true) {
        // stompp was already activated but is not currently hitting rules req.
        if (inputs->apps_percent < stompp_params.stomppAppsRecoveryThreshold) {
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
    stompp_active = false;
    outputs->output = STOMPP_OK;
}