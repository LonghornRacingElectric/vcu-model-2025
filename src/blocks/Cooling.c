//
// Created by henry on 1/8/2025.
//

#include "../../inc/blocks/Cooling.h"


void Cooling_evaluate(VcuParameters *params, CoolingInput *input, CoolingOutput *output, float deltaTime) {
    // this code outputs max cooling all the time
    output->pumpOutput = 1.0f;
    Lookup1D_evaluate(&params->coolingMotor, input->motorTemp);
    Lookup1D_evaluate(&params->coolingMotor, input->batteryTemp);
    // output->radiatorOutput = params->coolingMotor(input->motorTemp);
    // output->batteryFansOutput = params->coolingMotor(input->batteryTemp);
}
