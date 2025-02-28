
#include <gtest/gtest.h>

extern "C" {
    #include "../inc/VcuModel.h"
}

TEST(Vcu, NormalTest) {
    VCUModelParameters params = {
            .apps = {
                    .sensorInRangeUpperBound = 1.0f,
                    .sensorInRangeLowerBound = 0.0f,
                    .allowedPlausibilityRange = 0.1f,
                    .appsDeadzoneTopPercent = 0.0f,
                    .appsDeadzoneBottomPercent = 0.0f,
                    .appsMaxImplausibilityTime = 100.0f,
                    .pedal1Bias = 0.5f,
            },
            .stompp = {
                .mechanicalBrakeThreshold = 0.03f,
                .stomppAppsCutoffThreshold = 0.25f,
                .stomppAppsRecoveryThreshold = 0.05f,
            },
    };

    VCUModel_set_parameters(&params);

    VCUModelInputs inputs = {
            .apps = {
                    .pedal1Percent = 0.45f,
                    .pedal2Percent = 0.45f
            },
            .stompp = {
                .apps_percent = 0.0f,
                .bse_percent = 0.35f
            }
    };

    VCUModelOutputs outputs;

    VCUModel_evaluate(&inputs, &outputs, 0.01f);
}