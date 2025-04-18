/**
 * @file PIDController.h
 * @author Dhairya Gupta
 * @brief for creating PID controllers with different parameters. Internally
 * manages integral accumulation and differentiation.
 * @version 0.1
 * @date 2025-04-17
 */

#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H

typedef struct PIDController {
    // internal states/inputs
    float _kp;
    float _ki;
    float _kd;
    float _setpoint;
    float _error;
    float _integral;
    float _derivative;
    float _prevError;
    float _maxOutput;
    float _minOutput;
    float _integralLimit;
    float _derivativeLimit;
    float _integralResetLimit;

    // output
    float output;
} PIDController;

void PIDController_init(PIDController *pid, float kp, float ki, float kd,
                        float maxOutput, float minOutput, float integralLimit,
                        float derivativeLimit, float integralResetLimit);

float PIDController_evaluate(PIDController *pid, float currentValue,
                             float newSetpoint, float dt);

#endif  // PIDCONTROLLER_H