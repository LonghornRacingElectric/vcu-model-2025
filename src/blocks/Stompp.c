//
// Created by henry on 10/27/2024.
//

#include "../../inc/blocks/Stompp.h"

void Stompp_evaluate(Stompp* stompp, VcuParameters *params, StomppInput *input, StomppOutput *output, float deltatime) {
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
        stompp->stomppActive = true;
    }
    //To disable STOMPP, Accelerator Travel must fall under 5%
    if (stompp->stomppActive) {
        output->ok = false;
        if (input->pedal < params->stomppAppsRecoveryThreshold) {
            output->ok = true;
            stompp->stomppActive = false;
        }
    }

    //Check if STOMPP has been disabled
    if (!stompp->stomppActive)
        output->ok = true;

    output->fault = (!output->ok) * STOMPP_FAULT;
}

void Stompp_reset(Stompp* stompp) {
    stompp->stomppActive = false;
}
void Stompp_toggle(Stompp* stompp) {
    stompp->stomppActive = true;
}



