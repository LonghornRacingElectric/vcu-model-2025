//
// Created by Dhairya Gupta on 6/15/25.
//

#include "../../inc/blocks/ParkDriveSystem.h"

#include "usb_vcp.h"
#include "../../inc/util/Timer.h"

static ParkDriveParameters parkDriveParams;
static Timer buzzTimer;

static bool state_inDrive = false;

void ParkDriveSystem_setParams()
{
    // parkDriveParams = *params;
    // buzzTimer.duration = params->buzzerDuration;  // TODO wtf why doesn't this work
    Timer_init(&buzzTimer, 1.3f);
}

void ParkDriveSystem_evaluate(ParkDriveInputs* inputs, ParkDriveOutputs* outputs, float deltaTime)
{
    if (state_inDrive)
    {
        state_inDrive = inputs->tractiveSystemReady && inputs->driveSwitchEnabled;

        Timer_count(&buzzTimer, deltaTime);
        outputs->buzzerEnabled = !Timer_isFinished(&buzzTimer);
    }
    else
    {
        if (inputs->isDriverBraking && (inputs->appsPercent == 0)
            && inputs->tractiveSystemReady && inputs->driveSwitchEnabled)
        {
            state_inDrive = true;
            Timer_reset(&buzzTimer);
            outputs->buzzerEnabled = true;
        } else
        {
            outputs->buzzerEnabled = false;
        }
    }

    outputs->driveStateEnabled = state_inDrive;
    outputs->appsPercentSafe = inputs->appsPercentStompp * state_inDrive;
    // usb_printf("buzz: %.2f", buzzTimer.time);
}
