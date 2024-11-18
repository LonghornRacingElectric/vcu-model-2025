//
// Created by henry on 10/27/2024.
//

#include "../../inc/blocks/AppsProcessor.h"

void AppsProcessor::evaluate(VcuParameters *params, AppsProcessorInput *input,
                             AppsProcessorOutput *output, float deltaTime) {
    float diff = input->perc1 - input->perc2;
    if (diff < 0) {
        diff = -diff;
    }

    if (diff > params->appsPlausibilityRange) {
        differenceClock.count(deltaTime);
        if (differenceClock.isFinished()) {
            output->fault = APPS_DISAGREE;
            output->ok = !(APPS_SHUTDOWN_MASK & output->fault);
            output->perc = 0;
            return;
        }
    } else {
        differenceClock.reset();
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
}

void AppsProcessor::reset() { differenceClock.reset(); }
void AppsProcessor::setParameters(VcuParameters *params) {
    // Ask about apps implausibility time
}
