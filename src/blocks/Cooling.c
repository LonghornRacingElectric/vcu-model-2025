//
// Created by henry on 1/8/2025.
//

#include "../../inc/blocks/Cooling.h"
#include "util/Timer.h"

static CoolingParameters cooling_params;


void setParams(CoolingParameters *params){
    cooling_params = *params;
}

void cooling_motor(CoolingInput *input, CoolingOutput *output){
    output->pump1Output = 1.0f; //pumps for motor should be on all the time
    Lookup1D coolingMotor;
    Lookup1D_init(&coolingMotor, 20.0f, 1.0);

    //temp thresholds


    float fan_speed = 0.0f;


    if (input->motorRadInTemp >= cooling_params.motor_fan_on_threshold || input->motorRadOutTemp >= cooling_params.motor_fan_on_threshold || input->motorInverterTemp >= cooling_params.motor_fan_on_threshold){
        if (input->motorRadInTemp >= cooling_params.motor_fan_full_speed_threshold || input->motorRadOutTemp >= cooling_params.motor_fan_full_speed_threshold || input->motorInverterTemp >= cooling_params.motor_fan_full_speed_threshold){
            fan_speed = 1.0f;
        }
        else{
            fan_speed = Lookup1D_evaluate(&coolingMotor, input->motorInverterTemp-40.0f);
        }
    }
    output->motorFansOutput = fan_speed;

}

void cooling_bat(CoolingInput *input, CoolingOutput *output){
    if (input->battRadOutTemp >= input->ambientTemp){ //wait for battery temp to reach ambient temp
        output->pump2Output = 1.0f;
    }
    //temp thresholds


    //fan speed
    float fan_speed = 0.0f;

    //look up table
    Lookup1D coolingLookup;
    Lookup1D_init(&coolingLookup, 20.0f, 1.0);


    if (input->battRadInTemp >= cooling_params.batt_fan_on_threshold || input->battRadOutTemp >= cooling_params.batt_fan_on_threshold){
        if (input->battRadInTemp >= cooling_params.batt_fan_full_speed_threshold || input->battRadOutTemp >= cooling_params.batt_fan_full_speed_threshold){
            fan_speed = 1.0f;
        }
        else{
            fan_speed = Lookup1D_evaluate(&coolingLookup, input->battRadOutTemp);
        }
    }
    output->batteryFansOutput = fan_speed;


}