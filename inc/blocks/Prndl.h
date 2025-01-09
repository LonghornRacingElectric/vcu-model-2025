//
// Created by henry on 1/7/2025.
//

#ifndef PRNDL_H
#define PRNDL_H

#include "VcuParameters.h"
#include "util/Debounce.h"

typedef struct PrndlInput {
    bool driveSwitch; // true = drive
    bool inverterReady;
    float bse;
    float apps;
} PrndlInput;


typedef struct PrndlOutput {
    bool state; // true = drive
    bool buzzer; // true = buzz
} PrndlOutput;

class Prndl {
private:
    bool state = false;
    bool driveSwitchLastState = false;
    Debounce switchInputDebounce = Debounce(0, false);
    Timer buzzerTimer = Timer(0);
public:
    void setParameters(VcuParameters* params);
    void evaluate(VcuParameters *params, PrndlInput *input, PrndlOutput *output, float deltaTime);
};

#endif //PRNDL_H
