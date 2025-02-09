//
// Created by henry on 1/7/2025.
//

#include "../../inc/blocks/TractionControl.h"

/**
 * Reduce the driver's torque request when necessary to maintain traction.
 * This prevents the car from spinning out, giving the driver more confidence in acceleration.
 */

void TractionControl_setParameters(TractionControl* tractionControl, VcuParameters *params) {
    LowPassFilter_init(&tractionControl->lowPassFeedback, params->tcsFeedbackLowPassFilterTimeConstant);
    //tractionControl->lowPassFeedback = LowPassFilter(params->tcsFeedbackLowPassFilterTimeConstant);
}

void TractionControl_evaluate(TractionControl* tractionControl, VcuParameters *params, TractionControlInput *input, TractionControlOutput *output,
                               float deltaTime) {
    if(!params->tcsEnabled || !input->wheelSpeedsOk) {
        output->regulatedTorqueRequest = input->unregulatedTorqueRequest;
        return;
    }

    float averageFrontVelocity = (input->wheelSpeedFl + input->wheelSpeedFr) / 2.0f;
    float excessVelocityL = input->wheelSpeedBl - averageFrontVelocity;
    float excessVelocityR = input->wheelSpeedBr - averageFrontVelocity;
    float excessVelocity = (excessVelocityL > excessVelocityR) ? excessVelocityL : excessVelocityR;
    float excessSlip = (excessVelocity / averageFrontVelocity) - 0.15f;

    if(excessSlip < 0 || excessVelocity < 0.01f) {
        excessSlip = 0;
    }
    excessVelocity = excessSlip * averageFrontVelocity;
    LowPassFilter_add(&tractionControl->lowPassFeedback, excessVelocity, deltaTime);
    //lowPassFeedback.add(excessVelocity, deltaTime);
    excessVelocity = LowPassFilter_get(&tractionControl->lowPassFeedback);

    float negativeFeedback = 3.0f * excessVelocity;

    float maxTorque = 230.0f;
    float openLoopTorqueLimit = input->unregulatedTorqueRequest;
    if(input->unregulatedTorqueRequest > maxTorque) {
        openLoopTorqueLimit = maxTorque;
    }

    if(negativeFeedback > openLoopTorqueLimit) {
        negativeFeedback = openLoopTorqueLimit;
    }

    output->regulatedTorqueRequest = openLoopTorqueLimit - negativeFeedback;

}