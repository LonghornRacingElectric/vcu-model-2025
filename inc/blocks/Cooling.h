//
// Created by henry on 1/8/2025.
//

#ifndef COOLING_H
#define COOLING_H



#include "../VcuParameters.h"

//#define MOTOR_FAN_ON_THRESHOLD 40.0f
//#define MOTOR_FAN_FULL_SPEED_THRESHOLD 60.0f
//#define MOTOR_TEMP_DIFF_THRESHOLD 5.0f
//
//#define BATT_FAN_ON_THRESHOLD 30.0f
//#define BATT_FAN_FULL_SPEED_THRESHOLD 35.0f //shouldn't be higher than 60.0
//#define BATT_TEMP_DIFF_THRESHOLD 2.5f

typedef struct CoolingInputs {
    float battRadInTemp; //different sensors
    float battRadOutTemp;
    float motorRadInTemp;
    float motorRadOutTemp;
    float motorInverterTemp;
    float ambientTemp;
    int battTach; // assumed in RPM
    int motorTach;
} CoolingInputs;


typedef struct CoolingOutput {
    float pump1Output;
    float pump2Output;
    float motorFansOutput;
    float batteryFansOutput;
} CoolingOutputs;

typedef struct CoolingParameters{
    float motor_fan_on_threshold;
    float motor_fan_full_speed_threshold;
    float batt_fan_on_threshold;
    float batt_fan_full_speed_threshold;
}CoolingParameters;


void Cooling_motor_evaluate(CoolingInputs *input, CoolingOutputs *output);
void Cooling_batt_evaluate(CoolingInputs *input, CoolingOutputs *output);
void Cooling_setParameters(CoolingParameters *params);

#endif //COOLING_H
