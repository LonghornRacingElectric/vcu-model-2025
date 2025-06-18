/*

APPS Processor (Accelerator Pedal Pressure Sensors)

View header file for more information

Created by Dhairya & Henry on 2/27/2025

*/

#include "../../inc/blocks/BseProcessor.h"
#include <util/LowPassFilter.h>

#include "usb_vcp.h"

static BseParameters bseParams;

static Timer implausibilityTimer;
static LowPassFilter bseFFilter;
static LowPassFilter bseRFilter;


void BseProcessor_setParams(BseParameters* params)
{
  bseParams = *params;

  implausibilityTimer.duration = bseParams.bseMaxImplausibilityTime;
  LowPassFilter_init(&bseFFilter, bseParams.bseLowPassFilterTimeConstant);
  LowPassFilter_init(&bseRFilter, bseParams.bseLowPassFilterTimeConstant);
}

void BseProcessor_evaluate(BseInputs* inputs, BseOutputs* outputs,
                           float deltaTime)
{
  outputs->status = BSE_OK;

  bool bseFPlausible = (inputs->bseFVoltage >= bseParams.bseMinAllowableVoltage) && (inputs->bseFVoltage <= bseParams.
    bseMaxAllowableVoltage);
  bool bseRPlausible = (inputs->bseRVoltage >= bseParams.bseMinAllowableVoltage) && (inputs->bseRVoltage <= bseParams.
    bseMaxAllowableVoltage);

  outputs->bseFPressure = 0;
  outputs->bseRPressure = 0;

  float averagePressure = 0;
  float numPressures = 0;

  if (bseFPlausible)
  {
    LowPassFilter_add(&bseFFilter, inputs->bseFVoltage, deltaTime);
    float bseFPercent = (LowPassFilter_get(&bseFFilter) - bseParams.bseZeroPressureVoltage) /
      (bseParams.bseMaxPressureVoltage - bseParams.bseZeroPressureVoltage);
    float bseFPressure = bseFPercent * bseParams.bseMaxPressure;
    averagePressure += bseFPressure;
    numPressures += 1.0f;
    outputs->bseFPressure = bseFPressure;
  }
  else
  {
    LowPassFilter_reset(&bseFFilter);
  }

  if (bseRPlausible)
  {
    LowPassFilter_add(&bseRFilter, inputs->bseRVoltage, deltaTime);
    float bseRPercent = (LowPassFilter_get(&bseRFilter) - bseParams.bseZeroPressureVoltage) /
      (bseParams.bseMaxPressureVoltage - bseParams.bseZeroPressureVoltage);
    float bseRPressure = bseRPercent * bseParams.bseMaxPressure;
    averagePressure += bseRPressure;
    numPressures += 1.0f;
    outputs->bseRPressure = bseRPressure;
  }
  else
  {
    LowPassFilter_reset(&bseRFilter);
  }

  if (numPressures == 0)
  {
    // use last value if within timer, else fault
    Timer_count(&implausibilityTimer, deltaTime);
    if (Timer_isFinished(&implausibilityTimer))
    {
      outputs->status |= BSE_OUT_OF_RANGE;
    }

    outputs->bseAvgPressure = 0.0f;
    outputs->bseAvgPercent = 0.0f;
    outputs->isDriverBraking = false;
  }
  else
  {
    Timer_reset(&implausibilityTimer);

    outputs->bseAvgPressure = averagePressure / numPressures;
    outputs->bseAvgPercent = outputs->bseAvgPressure / bseParams.bseMaxPressure;
    outputs->isDriverBraking = outputs->bseAvgPressure > bseParams.bseBrakingPressure;
  }

}
