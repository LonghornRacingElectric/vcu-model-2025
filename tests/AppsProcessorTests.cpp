//
// Created by henry on 12/20/2024.
//


#include <gtest/gtest.h>
#include <src/gtest-internal-inl.h>

#include "VcuParameters.h"
#include "../inc/blocks/AppsProcessor.h"

TEST(AppsProcessor, AppsRulesCompliance) {
    AppsProcessor appsProcessor;
    AppsProcessorInput appsProcessorInput = {};
    AppsProcessorOutput appsProcessorOutput = {};

    VcuParameters vcuParameters;

    //APPS PARAMAETERS
    vcuParameters.appsPlausibilityRange = 0.10f; //(%)
    vcuParameters.appsDeadZoneBottomPct = 0.08f; // (%) of travel that is 0 or 100
    vcuParameters.appsDeadZoneTopPct = 0.13f; // (%) of travel that is 0 or 100
    vcuParameters.appsImplausibilityTime = 0.100f; // (s)

    AppsProcessor_setParameters(&appsProcessor, &vcuParameters);

    // Test 0% pedal travel
    appsProcessorInput = {0.0f, 0.0f};
    AppsProcessor_evaluate(&appsProcessor, &vcuParameters, &appsProcessorInput, &appsProcessorOutput, 1.0f);
    EXPECT_FLOAT_EQ(appsProcessorOutput.perc, 0.0f);
    EXPECT_TRUE(appsProcessorOutput.ok);
    AppsProcessor_reset(&appsProcessor);

    // Test 50% pedal travel
    appsProcessorInput = {0.5f, 0.599f};
    for(int i = 0; i < 100; i++)
        AppsProcessor_evaluate(&appsProcessor, &vcuParameters, &appsProcessorInput, &appsProcessorOutput, 0.001f);
    EXPECT_NEAR(appsProcessorOutput.perc, 0.5f, 0.1f);
    EXPECT_TRUE(appsProcessorOutput.ok);
    AppsProcessor_reset(&appsProcessor);

    // Test 100% pedal travel
    appsProcessorInput = {1.0f, 0.91f};
    for(int i = 0; i < 100; i++)
        AppsProcessor_evaluate(&appsProcessor, &vcuParameters, &appsProcessorInput, &appsProcessorOutput, 0.001f);
    EXPECT_NEAR(appsProcessorOutput.perc, 1.0f, 0.001f);
    EXPECT_TRUE(appsProcessorOutput.ok);
    AppsProcessor_reset(&appsProcessor);

    // Test implausibility
    appsProcessorInput = {1.0f, 0.0f};

    AppsProcessor_evaluate(&appsProcessor, &vcuParameters, &appsProcessorInput, &appsProcessorOutput, 1.0f);
    EXPECT_FALSE(appsProcessorOutput.ok);
    AppsProcessor_reset(&appsProcessor);

    // Test out of bounds 1
    appsProcessorInput = {-1.0f, -1.0f};
    AppsProcessor_evaluate(&appsProcessor, &vcuParameters, &appsProcessorInput, &appsProcessorOutput, 1.0f);
    EXPECT_FALSE(appsProcessorOutput.ok);
    AppsProcessor_reset(&appsProcessor);
    //
    // // Test out of bounds 2
    appsProcessorInput = {1.6f, 1.0f};
    AppsProcessor_evaluate(&appsProcessor, &vcuParameters, &appsProcessorInput, &appsProcessorOutput, 1.0f);
    EXPECT_FALSE(appsProcessorOutput.ok);
    AppsProcessor_reset(&appsProcessor);
    // // Test clock function
    appsProcessorInput = {0.7f, 0.64f};
    AppsProcessor_evaluate(&appsProcessor, &vcuParameters, &appsProcessorInput, &appsProcessorOutput, 0.09f);
    EXPECT_TRUE(appsProcessorOutput.ok);
    AppsProcessor_reset(&appsProcessor);
    //
    // // Test clock function
    appsProcessorInput = {0.9f, 0.64f};
    AppsProcessor_evaluate(&appsProcessor, &vcuParameters, &appsProcessorInput, &appsProcessorOutput, 0.11f);
    EXPECT_FALSE(appsProcessorOutput.ok);
    AppsProcessor_reset(&appsProcessor);
}