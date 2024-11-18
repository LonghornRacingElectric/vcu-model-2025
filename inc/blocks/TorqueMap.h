//
// Created by henry on 10/27/2024.
//

#ifndef TORQUEMAP_H
#define TORQUEMAP_H



#include "VcuParameters.h"



typedef struct TorqueMapInput {
    float apps; // pedal travel (%)
    float motorTemp; // (deg C)
    float motorRpm; // (rpm)
    float inverterTemp; // (deg C)
    float batteryTemp; // (deg C)
    float batterySoc; // (%)
    float batteryVoltage; // (V)
    float batteryCurrent; // (A)
} TorqueMapInput;


typedef struct TorqueMapOutput {
    float torqueRequest; // torque (Nm)
} TorqueMapOutput;


class TorqueMap {
public:
    void setParameters(VcuParameters* params);
    void evaluate(VcuParameters *params, TorqueMapInput *input, TorqueMapOutput *output, float deltaTime);
};




#endif //TORQUEMAP_H
