//
// Created by henry on 1/19/2025.
//

#include "../../inc/blocks/Indicator.h"

void Indicator_evaluate(VcuParameters *params, IndicatorOutput *output, IndicatorInput *input, float deltaTime) {
    if (!input->bmsFault && !input->imdFault) {
        output->greenOn = true;
        output->redFlash = false;
        return;
    } else {
        output->greenOn = false;
        output->redFlash = true;
        return;
    }
}

