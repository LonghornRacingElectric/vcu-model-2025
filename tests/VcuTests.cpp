
#include <gtest/gtest.h>
#include "VcuModel.h"

TEST(Vcu, NormalTorqueRequests) {
  VcuModel vcuModel;
  VcuParameters params;
  VcuInput input;
  VcuOutput output;

  // vcuModel.setParameters(&params);
  //
  // input.bse = 0.0;
  //
  // // apps 0%
  // input.apps1 = 0.0f;
  // input.apps2 = 0.02f;
  // vcuModel.evaluate(&input, &output, 0.1f);
  // EXPECT_NEAR(output.ineverterTorqueRequests, 0.0f, 1.0f);
  // printf("\napps: %.2f V, %.2f V\n", input.apps1, input.apps2);
  // printf("torque request: %.2f Nm\n", output.ineverterTorqueRequests);
  //
  // // apps 50%
  // input.apps1 = 0.5f;
  // input.apps2 = 0.5f;
  // vcuModel.evaluate(&input, &output, 0.1f);
  // EXPECT_NEAR(output.ineverterTorqueRequests, 115.0f, 10.0f);
  // printf("\napps: %.2f V, %.2f V\n", input.apps1, input.apps2);
  // printf("torque request: %.2f Nm\n", output.ineverterTorqueRequests);
  //
  // // apps 100%
  // input.apps1 = 0.91;
  // input.apps2 = 1.0f;
  // vcuModel.evaluate(&input, &output, 0.1f);
  // EXPECT_NEAR(output.ineverterTorqueRequests, 230.0f, 1.0f);
  // printf("\napps: %.2f V, %.2f V\n", input.apps1, input.apps2);
  // printf("torque request: %.2f Nm\n", output.ineverterTorqueRequests);

  printf("\n\n");


}