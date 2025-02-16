////
//// Created by henry on 10/27/2024.
////
//
//#include "../../inc/blocks/BrakeLight.h"
//
//#include <cstdint>
//
//// The accumulator provides a reliable, smooth brake signal that enables the
//// function to detect consistent braking pressure rather than reacting to every
//// small variation in input->bse
//
//void BreakLight_evaluate(BrakeLight *breaklight, VcuParameters *params, BreakLightInput *input,
//                          BreakLightOutput *output, float deltaTime) {
//    float percent = 0;
//
//    float tau = 0.1f;
//    float maxPercent = 0.5f;
//
//    float alpha = deltaTime / (deltaTime + tau);
//    breaklight->accumulator = (1.0f - alpha) * breaklight->accumulator + alpha * input->bse;
//    bool hardBraking = breaklight->accumulator > params->brakesHardThreshold ||
//                       breaklight->accumulator < -params->brakesHardThreshold;
//    bool braking = breaklight->accumulator > params->brakesSoftThreshold ||
//                   breaklight->accumulator < -params->brakesSoftThreshold;
//
//    if (hardBraking) {
//        bool pattern = (breaklight->brakeTimer > 0.5f) ||
//                       (static_cast<uint32_t>(breaklight->brakeTimer / 0.05f) % 2 == 0);
//        percent = pattern * maxPercent;
//        breaklight->brakeTimer += deltaTime;
//    } else if (braking) {
//        percent = maxPercent;
//        //  } else if (!input->parkOrDrive) {
//        //    time += deltaTime;
//        //    float sineWave = 0.5f * (sin(6.28f / 2.0f * (time - 1.0f))
//        //    + 1.0f); float pct = sineWave * 0.90f + 0.10f; percent = (pct *
//        //    pct * 0.4f); brakeTimer = 0;
//    } else {
//        percent = 0.0005f;
//        breaklight->brakeTimer = 0;
//    }
//
//    output->brakeLight = percent;
//}
