/*

STOMPP - See header file for details.

Created by Dhairya & Henry on 2/26/2025

*/

#include "../../inc/blocks/Stompp.h"

// state variable
static bool state_isStomppActive = false;

static StomppParameters stompp_params;

void Stompp_setParams(StomppParameters* params)
{
    stompp_params = *params;
}

void Stompp_evaluate(StomppInputs* inputs, StomppOutputs* outputs, float deltaTime)
{
    if (inputs->appsPercent >= stompp_params.stomppAppsCutoffThreshold && inputs->isDriverBraking)
    {
        state_isStomppActive = true;
    }
    else if (state_isStomppActive == true)
    {
        if (inputs->appsPercent < stompp_params.stomppAppsRecoveryThreshold)
        {
            state_isStomppActive = false;
        }
    }

    outputs->status = (state_isStomppActive) ? STOMPP_VIOLATED : STOMPP_OK;
    outputs->appsPercentStompp = (state_isStomppActive) ? 0.0f : inputs->appsPercent;
}
