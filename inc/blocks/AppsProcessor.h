//
// Created by henry on 10/27/2024.
//

#ifndef APPSPROCESSOR_H
#define APPSPROCESSOR_H

#include <stdint.h>


#include "VcuParameters.h"
#include "../util/Timer.h"

#define APPS_OK 0x00 // 0000
#define APPS_DISAGREE 0x01 // 0001


#define APPS_SHUTDOWN_MASK (APPS_DISAGREE)


typedef struct AppsProcessorInput {
    float perc1; // percentages are inverted one is invereted;
    float perc2; // ;
}AppsProcessorInput;

typedef struct AppsProcessorOutput {
    float perc; // pedal travel (%)
    uint32_t fault;
    bool ok;
}AppsProcessorOutput;

class AppsProcessor {
public:
    void reset();
    void evaluate(VcuParameters* params, AppsProcessorInput* input, AppsProcessorOutput* output, float deltaTime);
    void setParameters(VcuParameters* params);
private:
    //clocks and low pass filters
    Timer differenceClock = Timer(0.1f); //why??
};



#endif //APPSPROCESSOR_H
