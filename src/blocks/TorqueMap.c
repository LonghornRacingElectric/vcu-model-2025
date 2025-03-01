#include "../../inc/blocks/TorqueMap.h"

/**
 * Map a pedal travel percentage to a torque request.
 */

void TorqueMap_setParameters(TorqueMapParameters* params) {
    torque_map_params = *params;
}

void TorqueMap_evaluate(TorqueMapInputs* inputs, TorqueMapOutputs* outputs) {
    float torqueRequest = Lookup1D_evaluate(
        &torque_map_params.mapPedalToTorqueRequest, inputs->apps);

    outputs->torqueRequest = torqueRequest;
}