#include <gtest/gtest.h>

extern "C" {
#include "../inc/blocks/BrakeLight.h"
}

TEST(BrakeLight, LightOn) {
    BrakeLightParameters params = {.bseLightOnPercent = 0.5f,
                                   .bseTimeConstant = 0.1f};

    BrakeLight_setParameters(&params);

    BrakeLightInputs inputs = {.bsePercent = 0.6f};

    BrakeLightOutputs outputs;

    for (int i = 0; i < 20; i++) {
        BrakeLight_evaluate(&inputs, &outputs, 0.01f);
    }

    EXPECT_TRUE(outputs.lightOn);
}

TEST(BrakeLight, LightOff) {
    BrakeLightParameters params = {.bseLightOnPercent = 0.5f,
                                   .bseTimeConstant = 0.1f};

    BrakeLight_setParameters(&params);

    BrakeLightInputs inputs = {.bsePercent = 0.4f};

    BrakeLightOutputs outputs;

    BrakeLight_evaluate(&inputs, &outputs, 0.01f);

    EXPECT_FALSE(outputs.lightOn);
}

TEST(BrakeLight, FilterTest) {
    BrakeLightParameters params = {.bseLightOnPercent = 0.5f,
            .bseTimeConstant = 0.1f};

    BrakeLight_setParameters(&params);

    BrakeLightInputs inputs = {.bsePercent = 0.0f};

    BrakeLightOutputs outputs;

    BrakeLight_evaluate(&inputs, &outputs, 0.01f);
    EXPECT_FALSE(outputs.lightOn);

    inputs.bsePercent = 1.0f;
    BrakeLight_evaluate(&inputs, &outputs, 0.01f);
    EXPECT_FALSE(outputs.lightOn);
}