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

enum STOMPP_STATUS { STOMPP_OK, STOMPP_VIOLATED };

typedef struct StomppInputs
{
  float appsPercent;
  bool isDriverBraking;
} StomppInputs;

typedef struct StomppOutputs
{
  enum STOMPP_STATUS status;
  float appsPercentStompp;
} StomppOutputs;

typedef struct StomppParameters
{
  float stomppAppsCutoffThreshold; // Accelerator threshold % to use in tandem with brake threshold
  float stomppAppsRecoveryThreshold; // Accelerator min threshold to re-enable APPS
} StomppParameters;


void Stompp_setParams(StomppParameters* params);

void Stompp_evaluate(StomppInputs* inputs, StomppOutputs* outputs, float deltaTime);


#endif  // STOMPP_H
