//
// Created by henry on 10/27/2024.
//

#ifndef STOMPP_H
#define STOMPP_H

#include <stdint.h>
#include <stdbool.h>


#include "../VcuParameters.h"
#define STOMPP_OK 0x00
#define STOMPP_FAULT 0x01

typedef struct StomppInput {
    float pedal; // pedal travel (%)
    float bse; // break (%)
}StomppInput;

typedef struct StomppOutput {
    uint32_t fault; // pedal travel (%)
    bool ok; // break (%)
}StomppOutput;

typedef struct Stompp {
    bool stomppActive;
} Stompp;

#ifdef __cplusplus
extern "C" {
#endif


     void Stompp_reset(Stompp* stompp);
     void Stompp_toggle(Stompp* stompp);
     void Stompp_setParameters(Stompp* stompp, VcuParameters *vcuParameters);
     void Stompp_evaluate(Stompp* stompp, VcuParameters *params, StomppInput *input, StomppOutput *output, float deltatime);

#ifdef __cplusplus
}
#endif
// class Stompp {
// public:
//     void reset();
//     void toggleStompp();
//     void setParameters(VcuParameters *vcuParameters) {};
//     void evaluate(VcuParameters *params, StomppInput *input, StomppOutput *output, float deltatime);
// private:
//     bool stomppActive = false;
// };



#endif //STOMPP_H
