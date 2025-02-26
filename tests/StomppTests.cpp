
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
    
}