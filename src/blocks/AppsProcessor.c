//
// Created by henry on 10/27/2024.
//

#include "../../inc/blocks/AppsProcessor.h"

#include <iostream>
#include <ostream>

void AppsProcessor_evaluate(AppsProcessor* processor, VcuParameters *params, AppsProcessorInput *input,
                             AppsProcessorOutput *output, float deltaTime) {
    float diff = input->perc1 - input->perc2;
    if (diff < 0) {
        diff = -diff;
    }

    if (diff > params->appsPlausibilityRange) {
        Timer_count(&processor->differenceClock, deltaTime);

        if (Timer_isFinished(&processor->differenceClock)) {
            output->fault = APPS_DISAGREE;
            output->ok = false;
            output->perc = 0;
            return;
        }
    } else {
        Timer_reset(&processor->differenceClock);
    }

    output->fault = APPS_OK;
    output->ok = !(APPS_SHUTDOWN_MASK & output->fault);

    // ASK ABOUT THIS

    float appsNoDeadzone = (input->perc1 + input->perc2) / 2;
    float slope = 1.0f / (1.0f - params->appsDeadZoneTopPct -
                          params->appsDeadZoneBottomPct);

    if (appsNoDeadzone <= params->appsDeadZoneBottomPct) {
        output->perc = 0;
    } else if (appsNoDeadzone >= (1 - params->appsDeadZoneTopPct)) {
        output->perc = 1;
    } else {
        output->perc = slope * (appsNoDeadzone - params->appsDeadZoneBottomPct);
    }
    //std::cout << "perc " << output->perc << std::endl;
}

void AppsProcessor_reset(AppsProcessor* processor) {
    Timer_reset(&processor->differenceClock);
}
void AppsProcessor_setParameters(AppsProcessor* processor, VcuParameters *params) {
    // Ask about apps implausibility time
     Timer_init(&processor->differenceClock, params->appsImplausibilityTime);
    //this->differenceClock = Timer(params->appsImplausibilityTime);
}
