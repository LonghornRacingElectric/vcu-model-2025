//
// Created by henry on 10/27/2024.
//

#include "VcuModel.h"


void VcuModel_setParameters(VcuModel *vcu, VcuParameters *newParams) {
    vcu->params = newParams;
    AppsProcessor_setParameters(&vcu->appsProcessor, newParams);

    Stompp_setParameters(&vcu->stompp, newParams);
    TorqueMap_setParameters(newParams);

}

void VcuModel_evaluate(VcuModel* vcu, VcuInput *vcuInput, VcuOutput *vcuOutput, float deltaTime) {
    vcu->appsProcessorInput = {
        vcuInput->apps1,
        vcuInput->apps2
    };
    AppsProcessor_evaluate(&vcu->appsProcessor, vcu->params, &vcu->appsProcessorInput, &vcu->appsProcessorOutput, deltaTime);
    //appsProcessor.evaluate(params, &appsProcessorInput, &appsProcessorOutput, deltaTime);

    vcu->stomppInput = {
        vcu->appsProcessorOutput.perc,
        vcuInput->bse
    };
    Stompp_evaluate(&vcu->stompp, vcu->params, &vcu->stomppInput, &vcu->stomppOutput, deltaTime);
    //stompp.evaluate(params, &stomppInput, &stomppOutput, deltaTime);

    vcu->torqueMapInput = {
        vcu->appsProcessorOutput.perc,
        // vcuInput->motorTemp,
        // vcuInput->motorRpm,
        // vcuInput->inverterTemp,
        // vcuInput->hvBatteryTemp,
        // vcuInput->hvBatterySoc,
        // vcuInput->hvBatteryVoltage,
        // vcuInput->hvBatteryCurrent,
    };
    TorqueMap_evaluate(vcu->params, &vcu->torqueMapInput, &vcu->torqueMapOutput, deltaTime);
    //torqueMap.evaluate(params, &torqueMapInput, &torqueMapOutput, deltaTime);

    // breakLightInput = {
    //     vcuInput->bse
    // };
    // breakLight.evaluate(params, &breakLightInput, &breakLightOutput, deltaTime);

    *vcuOutput = {
        vcu->torqueMapOutput.torqueRequest
    };
}


#ifdef VCU_FIRMWARE_2025_SIL_H
#include "sil/pybind11/pybind11.h"

#endif
