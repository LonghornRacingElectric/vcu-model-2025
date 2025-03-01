////
//// Created by henry on 12/30/2024.
////
//#include <gtest/gtest.h>
//#include "VcuParameters.h"
//#include "../inc/blocks/TorqueMap.h"
//
//TEST(TorqueMap, PowerLimit) {
//    VcuParameters params;
//    Lookup1D torqueLookup;
//    Lookup1D_init(&torqueLookup, 1.0f, 230.0f);
//    params.mapPedalToTorqueRequest = torqueLookup;
//    // params.mapDerateBatterySoc = CurveParameter();
//    // params.mapDerateInverterTemp = CurveParameter();
//    // params.mapDerateInverterTemp = CurveParameter();
//    // params.mapDerateMotorTemp = CurveParameter();
//    // params.mapPowerLimit = 80000;
//    // params.mapPowerLimitFeedbackP = 0.01f;
//    // params.mapPowerLimitFeedbackTimeConstant = 0;
//
//    TorqueMapInputs torqueMapInput;
//    TorqueMapOutputs torqueMapOutput;
//
//    TorqueMap_setParameters(&params);
//
//    torqueMapInput = {
//        1.0f,
//        0.0f,
//        0.0f,
//        0.0f,
//        0.0f,
//        500.0f,
//        0.0f,
//};
//    TorqueMap_evaluate(&params, &torqueMapInput, &torqueMapOutput, 0.001f);
//    EXPECT_FLOAT_EQ(torqueMapOutput.torqueRequest, 230.0f);
//
//    torqueMapInput = {
//        1.0f,
//        0.0f,
//        0.0f,
//        0.0f,
//        0.0f,
//        500.0f,
//        1000.0f,
//};
//    TorqueMap_evaluate(&params, &torqueMapInput, &torqueMapOutput, 0.001f);
//    EXPECT_FLOAT_EQ(torqueMapOutput.torqueRequest, 230.0f);
//
//    torqueMapInput = {
//        1.0f,
//        0.0f,
//        0.0f,
//        0.0f,
//        0.0f,
//        500.0f,
//        200.0f,
//};
//    TorqueMap_evaluate(&params, &torqueMapInput, &torqueMapOutput, 0.001f);
//    EXPECT_FLOAT_EQ(torqueMapOutput.torqueRequest, 230.0f);
//}
