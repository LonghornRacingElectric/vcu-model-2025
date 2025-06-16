//
// Created by Dhairya Gupta on 6/15/25.
//

#include "../../inc/blocks/ParkDriveSystem.h"

#include "../../inc/util/Timer.h"

static STOMPPParameters params;
static bool inDrive;
static Timer timer;

void ParkDriveSystem_set_parameters(VCUModelParameters *parameters) {
    params = parameters->stompp;
    inDrive = false;
    timer.duration = 1.0f; // 1 second (?)
}


void ParkDriveSystem_evaluate(VCUModelInputs *inputs, VCUModelOutputs *outputs, float dt) {
    if(!inDrive) {
        // need to make sure brake pressed, not accel. Will use the braking threshold and accel thresdhold for this.
        if (inputs->stompp.bse_percent > params.mechanicalBrakeThreshold &&
            (inputs->stompp.apps_percent <= params.stomppAppsRecoveryThreshold)) {
            inDrive = inputs->drive_switch_enabled && inputs->tractive_system_active; // we can successfully go into drive (or whatever the switch is)

            if(inDrive) {
                // if we went into drive, reset timer and enable buzzer
                Timer_reset(&timer);
            }
        }
    } else {
        // if already in drive, we can just update it to whatever the latest CAN packet says.
        inDrive = inputs->drive_switch_enabled && inputs->tractive_system_active;

        // buzzerrrr (as long as it hasn't been a full second, keep the buzzer on).
        outputs->buzzer_enable = !Timer_isFinished(&timer);
        Timer_count(&timer, dt);
    }

    outputs->drive_enable = inDrive;
}
