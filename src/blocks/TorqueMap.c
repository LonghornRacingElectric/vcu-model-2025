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

    outputs->torqueRequest = torqueRequest;
}