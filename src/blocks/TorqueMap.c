#include "../../inc/blocks/TorqueMap.h"

/**
 * Map a pedal travel percentage to a torque request.
 */

static TorqueMapParameters torque_map_params;

void TorqueMap_setParameters(TorqueMapParameters* params) {
    torque_map_params = *params;
    Lookup1D_init(&torque_map_params.mapPedalToTorqueRequest);
}

void TorqueMap_evaluate(TorqueMapInputs* inputs, TorqueMapOutputs* outputs, float deltaTime) {
    // TODO derates

    float torqueCommand = Lookup1D_evaluate(
        &torque_map_params.mapPedalToTorqueRequest, inputs->appsPercentSafe);

    outputs->torqueCommand = torqueCommand;
    outputs->enableInverter = torqueCommand > 0.0f && inputs->appsPercentSafe > 0.0f;
}