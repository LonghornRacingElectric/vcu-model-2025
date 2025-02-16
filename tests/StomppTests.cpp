
#include <gtest/gtest.h>
#include "VcuParameters.h"
#include "blocks/AppsProcessor.h"
#include "../inc/blocks/Stompp.h"

//Check for two main requirements. Enable STOMPP IF:
//  Brakes are active
//  AND
//  Accelerator Travel > 25%

//Disable when
//  Accelerator Travel < 5%

TEST(Stompp, StomppRulesCompliance){
    Stompp stomppProcessor;
    StomppInput stomppInput = {};
    StomppOutput stomppOutput = {};

    VcuParameters vcuParameters = {};
    vcuParameters.stomppAppsCutoffThreshold = 0.25f; // apps pedal travel where motor power needs to be cut off (%)
    vcuParameters.stomppAppsRecoveryThreshold = 0.05f; // apps pedal travel where motor power can be restored (%)
    vcuParameters.stomppMechanicalBrakesThreshold = 0.1f;

    //Test 0% apps with no break pressure - Stompp remains disabled
    stomppInput = {0.0f, 0.0f};
    Stompp_evaluate(&stomppProcessor, &vcuParameters, &stomppInput, &stomppOutput, 1.0f);
    EXPECT_TRUE(stomppOutput.ok);
    Stompp_reset(&stomppProcessor);

    //Test 0%-100% accelerator travel with insignificant break pressure - Stompp remains disabled
    for(int appsInRange = 0; appsInRange < 100; appsInRange++) {
        stomppInput = {(float)(appsInRange)/100, 0.05f};
        Stompp_evaluate(&stomppProcessor, &vcuParameters, &stomppInput, &stomppOutput, 1.0f);
        EXPECT_TRUE(stomppOutput.ok);
        Stompp_reset(&stomppProcessor);
    }

    //Test 0% accelerator travel with full scale break pressure (0%-100%)
    for(float bseInRange = 0.0; bseInRange < 1.0; bseInRange+=0.01) {
        stomppInput = {0.0f, bseInRange};
        Stompp_evaluate(&stomppProcessor, &vcuParameters, &stomppInput, &stomppOutput, 1.0f);
        EXPECT_TRUE(stomppOutput.ok);
        Stompp_reset(&stomppProcessor);
    }

    //Test 26% accelerator travel with breaks applied
    stomppInput = {0.26f, 0.11f};
    Stompp_evaluate(&stomppProcessor, &vcuParameters, &stomppInput, &stomppOutput, 1.0f);
    EXPECT_FALSE(stomppOutput.ok);
    Stompp_reset(&stomppProcessor);

    //Test 0%-100% accelerator travel with breaks applied
    for(float appsInRange = 0.0; appsInRange < 1.0; appsInRange+=0.01) {
        stomppInput = {appsInRange, 0.11f};
        Stompp_evaluate(&stomppProcessor, &vcuParameters, &stomppInput, &stomppOutput, 1.0f);
        if(appsInRange > 0.25f)
            EXPECT_FALSE(stomppOutput.ok);
        else if(appsInRange <= 0.25f)
            EXPECT_TRUE(stomppOutput.ok);
        Stompp_reset(&stomppProcessor);
    }

    //Test 26% accelerator travel with full scale break pressure
    for(float bseInRange = 0; bseInRange < 1.0;  bseInRange+=0.01) {
        stomppInput = {0.26, (float)bseInRange};
        Stompp_evaluate(&stomppProcessor, &vcuParameters, &stomppInput, &stomppOutput, 1.0f);
        if((float)bseInRange > vcuParameters.stomppMechanicalBrakesThreshold)
            EXPECT_FALSE(stomppOutput.ok);
        else if((float)bseInRange <=vcuParameters.stomppMechanicalBrakesThreshold)
            EXPECT_TRUE(stomppOutput.ok);
        Stompp_reset(&stomppProcessor);
    }

    //Test if STOMPP disables when accelerator travel falls under 25 while brakes are applied
    Stompp_toggle(&stomppProcessor);
    for(int appsInRange = 100; appsInRange > 0; appsInRange--) {
        stomppInput = {(float) appsInRange / 100, 0.11};
        Stompp_evaluate(&stomppProcessor, &vcuParameters, &stomppInput, &stomppOutput, 1.0f);
        if (((float) appsInRange / 100) >= 0.05f)
            EXPECT_FALSE(stomppOutput.ok);
        else if (((float) appsInRange / 100) < 0.05f)
            EXPECT_TRUE(stomppOutput.ok);
    }
    Stompp_reset(&stomppProcessor);

    //Test if STOMPP disables when accelerator travel falls under 25 while brakes disabled
    Stompp_toggle(&stomppProcessor);
    for(int appsInRange = 100; appsInRange > 0; appsInRange--) {
        stomppInput = {(float) appsInRange / 100, 0.0f};
        Stompp_evaluate(&stomppProcessor, &vcuParameters, &stomppInput, &stomppOutput, 1.0f);
        if (((float) appsInRange / 100) >= 0.05f)
            EXPECT_FALSE(stomppOutput.ok);
        else if (((float) appsInRange / 100) < 0.05f)
            EXPECT_TRUE(stomppOutput.ok);
    }
    Stompp_reset(&stomppProcessor);
}