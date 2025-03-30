//
// Created by henry on 1/8/2025.
//

#include "../../inc/blocks/Cooling.h"
static CoolingParameters cooling_params;

static Lookup1D coolingMotor;

static Lookup1D coolingBatt;
void Cooling_setParameters(CoolingParameters *params){
    cooling_params = *params;
    coolingMotor.xP =  cooling_params.motor_fan_full_speed_threshold - cooling_params.motor_fan_on_threshold;
    coolingMotor.yP = 1.0f;
    coolingBatt.xP = cooling_params.batt_fan_full_speed_threshold - cooling_params.batt_fan_on_threshold;
    coolingBatt.yP = 1.0f;
}

void Cooling_motor_evaluate(CoolingInputs *input, CoolingOutputs *output){
    output->pump1Output = 1.0f; //pumps for motor should be on all the time


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

void Cooling_batt_evaluate(CoolingInputs *input, CoolingOutputs *output){
    if (input->battRadOutTemp >= input->ambientTemp){ //wait for battery temp to reach ambient temp
        output->pump2Output = 1.0f;
    }
    //temp thresholds


    //fan speed
    float fan_speed = 0.0f;

    //look up table


    if (input->battRadInTemp >= cooling_params.batt_fan_on_threshold || input->battRadOutTemp >= cooling_params.batt_fan_on_threshold){
        if (input->battRadInTemp >= cooling_params.batt_fan_full_speed_threshold || input->battRadOutTemp >= cooling_params.batt_fan_full_speed_threshold){
            fan_speed = 1.0f;
        }
        else{
            fan_speed = Lookup1D_evaluate(&coolingBatt, input->battRadOutTemp);
        }
    }
    output->batteryFansOutput = fan_speed;


}