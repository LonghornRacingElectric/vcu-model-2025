#include "../../inc/blocks/TorqueMap.h"

/**
 * Map a pedal travel percentage to a torque request.
 */

static TorqueMapParameters torque_map_params;

void TorqueMap_setParameters(TorqueMapParameters* params) {
    torque_map_params = *params;
    Lookup1D_init(&torque_map_params.mapPedalToTorqueRequest);
}

void TorqueMap_evaluate(TorqueMapInputs* inputs, TorqueMapOutputs* outputs) {
    float torqueRequest = Lookup1D_evaluate(
        &torque_map_params.mapPedalToTorqueRequest, inputs->apps);

    LowPassFilter_add(&torque_map_params.currentOvershootFilter,inputs->batteryCurrent, torque_map_params.deltaTime);

    if(inputs->batteryCurrent > -1.0f && inputs->batteryCurrent < 1.0f) {

    LowPassFilter_add(&torque_map_params.openCircuitVoltageFilter,inputs->batteryVoltage, torque_map_params.deltaTime);
    }
    float openCircuitVoltage = LowPassFilter_get(&torque_map_params.openCircuitVoltageFilter)
    float internalResistance = 0.750; // Ohms, estimated

    float currentLimit = 200.0f; // Amps (reduced from 230A)
    float currentBasedPowerLimit = (openCircuitVoltage - (currentLimit * internalResistance)) * currentLimit;
    float powerLimit = torque_map_params.mapPowerLimit;
    if(currentBasedPowerLimit < powerLimit) {
        powerLimit = currentBasedPowerLimit;
    }
    if(powerLimit < 0) {
        powerLimit = 0;
    }

    float smoothedCurrent = LowPassFilter_get(&torque_map_params.currentOvershootFilter);
    float currentPower = inputs->batteryVoltage * inputs->batteryCurrent;
    if(smoothedCurrent > 240.0f || currentPower > 85000.0f) {
        torqueRequest = 0;
    }

    float powerError = powerLimit - currentPower;
    torque_map_params.integral += powerError * torque_map_params.deltaTime;
    if(torque_map_params.integral > 0) {
        torque_map_params.integral = 0;
    }
    if(powerError > 0) {
        powerError = 0;
    }
    float derivative = (powerError - torque_map_params.prevError)/torque_map_params.deltaTime;
    float feedback = torque_map_params.kp * powerError + torque_map_params.ki * torque_map_params.integral + torque_map_params.kd * derivative;

    if(feedback > 0) {
        feedback = 0;
    }
    torqueRequest += feedback; // feedback is negative
    if(torqueRequest < 0) {
        torqueRequest = 0;
    }

    outputs->torqueRequest = torqueRequest;

    // outputs->ocvEstimate = openCircuitVoltage;
    // outputs->powerLimit = powerLimit;
    // outputs->feedbackP = powerError;
    // outputs->feedbackI = this->integral;
    // outputs->feedbackD = derivative;
    // outputs->feedbackTorque = feedback;

    torque_map_params.prevError = powerError;
    outputs->torqueRequest = torqueRequest;
}