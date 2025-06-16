/*

STOMPP handles FSAE EV.4.7 (APPS / Brake Pedal Plausibility Check)

Checks whether or not the current inputs on the APPS are past limits and follows
the states provided in rules.

Created by Dhairya & Henry on 2/26/2025

*/

#ifndef STOMPP_H
#define STOMPP_H

#include <stdbool.h>
#include <stdint.h>

#include "../VcuParameters.h"

enum STOMPP_OUTPUT { STOMPP_OK, STOMPP_FAULT };

typedef struct STOMPPInputs {
    float apps_percent;  // percentages
    float bse_percent;   // brake system encoder
} STOMPPInputs;

typedef struct STOMPPOutputs {
    enum STOMPP_OUTPUT output;  // STOMPP_OK is 0x0, non-zero if error/fault
    bool drive_enable, buzzer_enable;
} STOMPPOutputs;

typedef struct STOMPPParameters {
    float mechanicalBrakeThreshold;   // Brake threshold % before pedals cut off
                                      // (if the accelerator is also enabled)
    float stomppAppsCutoffThreshold;  // Accelerator threshold % to use in
                                      // tandem with brake threshold
    float stomppAppsRecoveryThreshold;  // Accelerator min threshold to
                                        // re-enable APPS
} STOMPPParameters;


void STOMPP_set_parameters(STOMPPParameters *params);

void STOMPP_evaluate(STOMPPInputs *inputs, STOMPPOutputs *outputs);

void STOMPP_enable(STOMPPOutputs *outputs);
void STOMPP_disable(STOMPPOutputs *outputs);

#endif  // STOMPP_H
