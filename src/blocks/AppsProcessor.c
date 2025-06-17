/*

APPS Processor (Accelerator Pedal Pressure Sensors)

View header file for more information

Created by Dhairya & Henry on 2/27/2025

*/

#include "../../inc/blocks/AppsProcessor.h"
#include <util/LowPassFilter.h>

static AppsParameters appsParams;

static Timer implausibilityTimer;
static LowPassFilter apps1Filter;
static LowPassFilter apps2Filter;



void AppsProcessor_setParams(AppsParameters *params) {
    appsParams = *params;

    implausibilityTimer.duration = appsParams.appsMaxImplausibilityTime;
    LowPassFilter_init(&apps1Filter, appsParams.appsLowPassFilterTimeConstant);
    LowPassFilter_init(&apps2Filter, appsParams.appsLowPassFilterTimeConstant);
}

void AppsProcessor_evaluate(AppsInputs *inputs, AppsOutputs *outputs,
                            float deltaTime) {

    outputs->status = APPS_OK;

    bool apps1InRange = (inputs->apps1Voltage >= appsParams.apps1VoltageMin) && (inputs->apps1Voltage <= appsParams.apps1VoltageMax);
    bool apps2InRange = (inputs->apps2Voltage >= appsParams.apps2VoltageMin) && (inputs->apps2Voltage <= appsParams.apps2VoltageMax);

    if (!apps1InRange || !apps2InRange) {
        Timer_count(&implausibilityTimer, deltaTime);
        if (Timer_isFinished(&implausibilityTimer)) {
            outputs->status |= APPS_OUT_OF_RANGE;
            outputs->appsPercent = 0;
            outputs->apps1Percent = 0;
            outputs->apps2Percent = 0;
            LowPassFilter_reset(&apps1Filter);
            LowPassFilter_reset(&apps2Filter);
            return;
        }
    } else {
        Timer_reset(&implausibilityTimer);
    }

    if(apps1InRange) LowPassFilter_add(&apps1Filter, inputs->apps1Voltage, deltaTime);
    if(apps2InRange) LowPassFilter_add(&apps2Filter, inputs->apps2Voltage, deltaTime);


    float apps1Percent = LowPassFilter_get(&apps1Filter) - appsParams.apps1VoltageMin /
        (appsParams.apps1VoltageMax - appsParams.apps1VoltageMin);
    float apps2Percent = LowPassFilter_get(&apps2Filter) - appsParams.apps2VoltageMin /
        (appsParams.apps2VoltageMax - appsParams.apps2VoltageMin);
    outputs->apps1Percent = apps1Percent;
    outputs->apps2Percent = apps2Percent;

    float diff = apps1Percent - apps2Percent;
    if (diff < 0) { diff = -diff; }

    if (diff > appsParams.allowedPlausibilityRange) {
        Timer_count(&implausibilityTimer, deltaTime);
        if (Timer_isFinished(&implausibilityTimer)) {
            outputs->status |= APPS_DISAGREE;
            outputs->appsPercent = 0;
            LowPassFilter_reset(&apps1Filter);
            LowPassFilter_reset(&apps2Filter);
            return;
        }
    } else {
        Timer_reset(&implausibilityTimer);
    }

    float appsNoDeadzone = (apps1Percent + apps2Percent) / 2.0f;

    if (appsNoDeadzone <= appsParams.appsDeadzoneBottomPercent) {
        outputs->appsPercent = 0;
    } else if (appsNoDeadzone >= (1.0f - appsParams.appsDeadzoneTopPercent)) {
        outputs->appsPercent = 1.0f;
    } else {
        float slope = 1.0f / (1.0f - appsParams.appsDeadzoneTopPercent - appsParams.appsDeadzoneBottomPercent);
        outputs->appsPercent = slope * (appsNoDeadzone - appsParams.appsDeadzoneBottomPercent);
    }
}
