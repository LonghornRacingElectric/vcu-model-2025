//
// Created by henry on 10/27/2024.
//

#include "../../inc/blocks/Stompp.h"

void Stompp::evaluate(VcuParameters *params, StomppInput *input, StomppOutput *output, float deltatime) {
    //"stomppActive = false" means "output.ok = true"
    //"output.ok = true" means motor functions normally

    //"stomppActive = true" means "output.ok = false"
    //"output.ok = false" means motor is disabled

    //Check for two main requirements. Enable STOMPP IF:
    //  Brakes are active
    //  Accelerator Travel > 25%

    //Check for two main requirements. Enable STOMPP IF:
    //  Brakes are active
    //  Accelerator Travel > 25%
    if ((input->bse > params->stomppMechanicalBrakesThreshold) && (input->pedal > params->stomppAppsCutoffThreshold)) {
        output->ok = false;
        stomppActive = true;
    }
    //To disable STOMPP, Accelerator Travel must fall under 5%
    if (stomppActive) {
        output->ok = false;
        if (input->pedal < params->stomppAppsRecoveryThreshold) {
            output->ok = true;
            stomppActive = false;
        }
    }

    //Check if STOMPP has been disabled
    if (!stomppActive)
        output->ok = true;

    output->fault = (!output->ok) * STOMPP_FAULT;
}

void Stompp::reset() {
    stomppActive = false;
}
void Stompp::toggleStompp() {
    stomppActive = true;
}



