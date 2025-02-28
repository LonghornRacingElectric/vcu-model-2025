//
// Created by henry on 12/20/2024.
//

#include <gtest/gtest.h>

#include "VcuParameters.h"

extern "C" {
#include "../inc/blocks/AppsProcessor.h"
#include "../inc/blocks/Stompp.h"
}

TEST(AppsProcessor, BasicCompliance) {
    APPSParameters params = {
            .sensorInRangeUpperBound = 1.0f,
            .sensorInRangeLowerBound = 0.0f,
            .allowedPlausibilityRange = 0.1f,
            .appsDeadzoneTopPercent = 0.0f,
            .appsDeadzoneBottomPercent = 0.0f,
            .appsMaxImplausibilityTime = 100.0f,
            .pedal1Bias = 0.5f,
    };

    APPSInputs inputs;
    APPSOutputs outputs;

    inputs.pedal1Percent = 0.45f;
    inputs.pedal2Percent = 0.45f;

    APPSProcessor_set_parameters(&params);

    APPSProcessor_evaluate(&inputs, &outputs, 0.01f);

    EXPECT_EQ(outputs.status, APPS_OK);
    EXPECT_FLOAT_EQ(outputs.pedalPercent, 0.45f);
}

TEST(AppsProcessor, BiasTest) {
    APPSParameters params = {
            .sensorInRangeUpperBound = 1.0f,
            .sensorInRangeLowerBound = 0.0f,
            .allowedPlausibilityRange = 0.1f,
            .appsDeadzoneTopPercent = 0.1f,
            .appsDeadzoneBottomPercent = 0.2f,
            .appsMaxImplausibilityTime = 100.0f,
            .pedal1Bias = 0.5f,
    };

    APPSInputs inputs;
    APPSOutputs outputs;

    inputs.pedal1Percent = 0.45f;
    inputs.pedal2Percent = 0.45f;

    APPSProcessor_set_parameters(&params);

    APPSProcessor_evaluate(&inputs, &outputs, 0.01f);

    EXPECT_EQ(outputs.status, APPS_OK);
    EXPECT_FLOAT_EQ(0.35714284f, outputs.pedalPercent);
}
