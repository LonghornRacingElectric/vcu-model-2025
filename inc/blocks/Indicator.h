//
// Created by henry on 1/19/2025.
//

#ifndef INDICATOR_H
#define INDICATOR_H
#include <VcuParameters.h>

#endif //INDICATOR_H

typedef struct IndicatorInput {
    bool bmsFault;
    bool imdFault;
} IndicatorInput;
typedef struct IndicatorOutput {
    bool greenOn;
    bool redFlash;
}IndicatorOutput;

class Indicator {
    public:
    void setParameters(VcuParameters *params);
    void evaluate(VcuParameters *params, IndicatorOutput *output, IndicatorInput *input, float deltaTime);
}
