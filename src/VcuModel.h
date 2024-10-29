//
// Created by henry on 10/27/2024.
//

#ifndef VCUMODEL_H
#define VCUMODEL_H

// include all the blocks and vcu params

#include "VcuParameters.h"
#include "../blocks/AppsProcessor.h"
#include "../blocks/Stompp.h"
#include "../blocks/TorqueMap.h"
#include "../blocks/BreakLight.h"


typedef struct VcuInput {
    float apps1; // apps1 percentage
    float apps2; // apps2 percentage

    float bse; // Assume i get one bse percentage/may change later

    bool driveSwitch; // (true = D, false = P)

} VcuInput;
typedef struct VcuOutput {
    //bool enableInverter;
    float ineverterTorqueRequests; // torque(Nm)
}VcuOutput;


class VcuModel {
private:
    //instatiate all block objects
    VcuParameters *params;

    AppsProcessor appsProcessor;
    AppsProcessorInput appsProcessorInput;
    AppsProcessorOutput appsProcessorOutput;

    Stompp stompp;
    StomppInput stomppInput;
    StomppOutput stomppOutput;

    TorqueMap torqueMap;
    TorqueMapInput torqueMapInput;
    TorqueMapOutput torqueMapOutput;

    BreakLight breakLight;
    BreakLightInput breakLightInput;
    BreakLightOutput breakLightOutput;
public:
    void setParameters(VcuParameters *newParams);
    void evaluate(VcuInput *input, VcuOutput *output, float deltaTime);
};



#endif //VCUMODEL_H
