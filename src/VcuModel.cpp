//
// Created by henry on 10/27/2024.
//

#include "VcuModel.h"


void VcuModel::setParameters(VcuParameters *newParams) {
    this->params = newParams;
    this->appsProcessor.setParameters(newParams);

    this->stompp.setParameters(newParams);
    this->torqueMap.setParameters(newParams);

}

void VcuModel::evaluate(VcuInput *vcuInput, VcuOutput *vcuOutput, float deltaTime) {
    appsProcessorInput = {
        vcuInput->apps1,
        vcuInput->apps2
    };
    appsProcessor.evaluate(params, &appsProcessorInput, &appsProcessorOutput, deltaTime);

    stomppInput = {
        appsProcessorOutput.perc,
        vcuInput->bse
    };
    stompp.evaluate(params, &stomppInput, &stomppOutput, deltaTime);

    torqueMapInput = {
        appsProcessorOutput.perc,
        // vcuInput->motorTemp,
        // vcuInput->motorRpm,
        // vcuInput->inverterTemp,
        // vcuInput->hvBatteryTemp,
        // vcuInput->hvBatterySoc,
        // vcuInput->hvBatteryVoltage,
        // vcuInput->hvBatteryCurrent,
    };
    torqueMap.evaluate(params, &torqueMapInput, &torqueMapOutput, deltaTime);

    breakLightInput = {
        vcuInput->bse
    };
    breakLight.evaluate(params, &breakLightInput, &breakLightOutput, deltaTime);

    *vcuOutput = {
        torqueMapOutput.torqueRequest
    };
}


#ifdef VCU_FIRMWARE_2025_SIL_H
#include "sil/pybind11/pybind11.h"

#endif
