
#include <gtest/gtest.h>
#include "VcuParameters.h"
#include "blocks/AppsProcessor.h"

extern "C" {
#include "../inc/blocks/Stompp.h"
}

//Check for two main requirements. Enable STOMPP IF:
//  Brakes are active
//  AND
//  Accelerator Travel > 25%

//Disable when
//  Accelerator Travel < 5%

TEST(Stompp, ValidNoBraking){
    STOMPPParameters params = {
            .stomppAppsRecoveryThreshold = 0.05f,
            .mechanicalBrakeThreshold = 0.03f,
            .stomppAppsCutoffThreshold = 0.25f
    };

    STOMPP_set_parameters(&params);

    STOMPPInputs inputs = {
            .apps_percent = 0.50f,
            .bse_percent = 0.0f
    };

    STOMPPOutputs outputs;

    STOMPP_evaluate(&inputs, &outputs);

    EXPECT_EQ(outputs.output, STOMPP_OK);
    std::cout << "Passed test" << std::endl;
}

TEST(Stompp, InvalidWithBraking){
    STOMPPParameters params = {
            .stomppAppsRecoveryThreshold = 0.05f,
            .mechanicalBrakeThreshold = 0.03f,
            .stomppAppsCutoffThreshold = 0.25f
    };

    STOMPP_set_parameters(&params);

    STOMPPInputs inputs = {
            .apps_percent = 0.50f,
            .bse_percent = 0.5f
    };

    STOMPPOutputs outputs;

    STOMPP_evaluate(&inputs, &outputs);

    EXPECT_EQ(outputs.output, STOMPP_FAULT);

    std::cout << "Passed test" << std::endl;
}

TEST(Stompp, InvalidWithBrakingRecovery){
    STOMPPParameters params = {
            .stomppAppsRecoveryThreshold = 0.05f,
            .mechanicalBrakeThreshold = 0.03f,
            .stomppAppsCutoffThreshold = 0.25f
    };

    STOMPP_set_parameters(&params);

    STOMPPInputs inputs = {
            .apps_percent = 0.50f,
            .bse_percent = 0.5f
    };

    STOMPPOutputs outputs;

    STOMPP_evaluate(&inputs, &outputs);

    EXPECT_EQ(outputs.output, STOMPP_FAULT);

    std::cout << "Passed braking, testing recovery" << std::endl;

    inputs.bse_percent = 0.0f;
    inputs.apps_percent = 0.0f;

    STOMPP_evaluate(&inputs, &outputs);

    EXPECT_EQ(outputs.output, STOMPP_OK);

    std::cout << "Passed recovery" << std::endl;
}

TEST(Stompp, InvalidWithBrakingRecoveryLate) {
    STOMPPParameters params = {
            .stomppAppsRecoveryThreshold = 0.05f,
            .mechanicalBrakeThreshold = 0.03f,
            .stomppAppsCutoffThreshold = 0.25f
    };

    STOMPP_set_parameters(&params);

    STOMPPInputs inputs = {
            .apps_percent = 0.50f,
            .bse_percent = 0.5f
    };

    STOMPPOutputs outputs;

    STOMPP_evaluate(&inputs, &outputs);
    EXPECT_EQ(outputs.output, STOMPP_FAULT);

    inputs.apps_percent = 0.23f;
    // should be no change in output
    STOMPP_evaluate(&inputs, &outputs);
    EXPECT_EQ(outputs.output, STOMPP_FAULT);

    std::cout << "Passed braking, testing recovery" << std::endl;

    inputs.bse_percent = 0.3f;
    inputs.apps_percent = 0.04f;

    STOMPP_evaluate(&inputs, &outputs);

    EXPECT_EQ(outputs.output, STOMPP_OK);
}