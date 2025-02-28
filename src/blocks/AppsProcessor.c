/*

APPS Processor (Accelerator Pedal Pressure Sensors)

View header file for more information

Created by Dhairya & Henry on 2/27/2025

*/

#include "../../inc/blocks/AppsProcessor.h"

void APPSProcessor_set_parameters(APPSParameters *params) {
    apps_params = *params;

    // set the timer duration
    timer.duration = apps_params.appsMaxImplausibilityTime;
}

void APPSProcessor_evaluate(APPSInputs *inputs, APPSOutputs *output,
                            float deltaTime) {
    bool pedal1OutOfRange =
        (inputs->pedal1Percent < apps_params.sensorInRangeLowerBound) ||
        (inputs->pedal1Percent > apps_params.sensorInRangeUpperBound);
    bool pedal2OutOfRange =
        (inputs->pedal2Percent < apps_params.sensorInRangeLowerBound) ||
        (inputs->pedal2Percent > apps_params.sensorInRangeUpperBound);

    // A sensor is out of range -- throw error and don't allow car to drive.
    if (pedal1OutOfRange || pedal2OutOfRange) {
        output->pedalPercent = 0.0f;
        output->status = APPS_OUT_OF_RANGE;
        return;
    }

    float delta = inputs->pedal1Percent - inputs->pedal2Percent;

    if (delta < 0)
        delta *= -1;  // invert in case it is negative (absolute value)

    if (delta > apps_params.allowedPlausibilityRange) {
        // run timer and if we exceed the amount of time allowed by the rules,
        // we fault
        Timer_count(&timer, deltaTime);
        if (Timer_isFinished(&timer)) {
            output->pedalPercent = 0.0f;
            output->status = APPS_DISAGREE;
            return;
        }
    } else {
        // we are within the valid range, reset the timer
        Timer_reset(&timer);
    }

    // before accounting for the deadzone, what is our expected pedal %?
    float appsNoDeadzone =
        (inputs->pedal1Percent * apps_params.pedal1Bias +
         inputs->pedal2Percent * (1.0f - apps_params.pedal1Bias));

    output->status = APPS_OK;  // we are good, no errors

    // the multiplier we need to use to get the actual output %
    float slope = 1.0f / (1.0f - apps_params.appsDeadzoneTopPercent -
                          apps_params.appsDeadzoneBottomPercent);

    if (appsNoDeadzone <= apps_params.appsDeadzoneBottomPercent) {
        appsNoDeadzone = 0.0f;
    } else if (appsNoDeadzone >= (1.0f - apps_params.appsDeadzoneTopPercent)) {
        output->pedalPercent = 1.0f;  // max
    } else {
        // somewhere in between, do some calculations
        output->pedalPercent =
            slope * (appsNoDeadzone - apps_params.appsDeadzoneBottomPercent);
    }
}
