//
// Created by henry on 1/8/2025.
//

#ifndef STEERING_H
#define STEERING_H

#include "../VcuParameters.h"


typedef struct SteeringInput {
    float steeringPotVoltage; // (Volts)
} SteeringInput;


typedef struct SteeringOutput {
    float steeringWheelAngle; // (degrees)
    float wheelAngleFl; // (radians)
    float wheelAngleFr;
    float wheelAngleBl;
    float wheelAngleBr;
} SteeringOutput;

//void setParameters(VcuParameters* params) {};
void evaluate(VcuParameters *params, SteeringInput *input, SteeringOutput *output, float deltaTime);

// class Steering {
// public:
//     void setParameters(VcuParameters* params) {};
//     void evaluate(VcuParameters *params, SteeringInput *input, SteeringOutput *output, float deltaTime);
// };


#endif //STEERING_H
