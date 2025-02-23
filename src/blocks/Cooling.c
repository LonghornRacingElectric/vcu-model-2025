//
// Created by henry on 1/8/2025.
//

#include "../../inc/blocks/Cooling.h"
#include "util/Timer.h"


void cooling_motor(VcuParameters *params, CoolingInput *input, CoolingOutput *output){
    output->pump1Output = 1.0f; //pumps for motor should be on all the time
    Lookup1D radLookup;
    Lookup1D_init(&radLookup, 1.0, 24.0);

    //temp thresholds


    float fan_speed = 0.0f;


    if (input->motorRadInTemp >= MOTOR_FAN_ON_THRESHOLD || input->motorRadOutTemp >= MOTOR_FAN_ON_THRESHOLD || input->motorInverterTemp >= MOTOR_FAN_ON_THRESHOLD){
        if (input->motorRadInTemp >= MOTOR_FAN_FULL_SPEED_THRESHOLD || input->motorRadOutTemp >= MOTOR_FAN_FULL_SPEED_THRESHOLD || input->motorInverterTemp >= MOTOR_FAN_FULL_SPEED_THRESHOLD){
            fan_speed = 1.0f;
        }
        else{
            fan_speed = (input->motorInverterTemp - MOTOR_FAN_ON_THRESHOLD)/MOTOR_FAN_FULL_SPEED_THRESHOLD;
        }
    }
    output->motorFansOutput = fan_speed;

    float delta_temp = input->motorRadInTemp - input->motorRadOutTemp;

    //this is #superscuffed
    Timer check;
    Timer_init(&check, 5); // wait 5 seconds
//    for (int i = 0; i < 5; i++) {
        Timer_count(&check, 1);
//    }
    if (Timer_isFinished(&check)){ //timer is done
        if (delta_temp < MOTOR_TEMP_DIFF_THRESHOLD) {
            fan_speed = 1.0f; // If radiator isn't cooling well, max fan speed
        }
    }
    output->motorFansOutput = fan_speed;
}

void cooling_bat(VcuParameters *params, CoolingInput *input, CoolingOutput *output){
    if (input->battRadOutTemp >= input->ambientTemp){ //wait for battery temp to reach ambient temp
        output->pump2Output = 1.0f;
    }
    //temp thresholds


    //fan speed
    float fan_speed = 0.0f;

    //look up table
    Lookup1D coolingLookup;
    Lookup1D_init(&coolingLookup, 1.0, 24.0);


    if (input->battRadInTemp >= BATT_FAN_ON_THRESHOLD || input->battRadOutTemp >= BATT_FAN_ON_THRESHOLD){
        if (input->battRadInTemp >= BATT_FAN_FULL_SPEED_THRESHOLD || input->battRadOutTemp >= BATT_FAN_FULL_SPEED_THRESHOLD){
            fan_speed = 1.0f;
        }
        else{
            fan_speed = (input->battRadOutTemp - BATT_FAN_ON_THRESHOLD)/BATT_FAN_FULL_SPEED_THRESHOLD;
        }
    }
    output->batteryFansOutput = fan_speed;

    //this is still #superscuffed
    float delta_temp = input->battRadOutTemp - input->battRadInTemp;
    Timer check;
    Timer_init(&check, 5); // wait 5 seconds
    for (int i = 0; i < 5; i++) {
        Timer_count(&check, 1);
    }
    if (Timer_isFinished(&check)){ //timer is done
        if (delta_temp < TBATT)EMP_DIFF_THRESHOLD) {
            fan_speed = 1.0f; // if hasn't cooled enough, max fan speed
        }
    }
    output->motorFansOutput = fan_speed;
}