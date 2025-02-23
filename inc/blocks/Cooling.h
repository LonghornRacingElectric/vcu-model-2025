//
// Created by henry on 1/8/2025.
//

#ifndef COOLING_H
#define COOLING_H



#include "../VcuParameters.h"

#define MOTOR_FAN_ON_THRESHOLD 40.0f
#define MOTOR_FAN_FULL_SPEED_THRESHOLD 60.0f
#define MOTOR_TEMP_DIFF_THRESHOLD 5.0f

#define BATT_FAN_ON_THRESHOLD 30.0f
#define BATT_FAN_FULL_SPEED_THRESHOLD 35.0f //shouldn't be higher than 60.0
#define BATT_TEMP_DIFF_THRESHOLD 2.5f

typedef struct CoolingInput {
    float battRadInTemp; //different sensors
    float battRadOutTemp;
    float motorRadInTemp;
    float motorRadOutTemp;
    float motorInverterTemp;
    float ambientTemp;
    int battTach; // assumed in RPM
    int motorTach;
} CoolingInput;


typedef struct CoolingOutput {
    float pump1Output;
    float pump2Output;
    float motorFansOutput;
    float batteryFansOutput;
} CoolingOutput;



void Cooling_evaluate(VcuParameters *params, CoolingInput *input, CoolingOutput *output, int desiredRPM);


#endif //COOLING_H
