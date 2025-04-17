/**
 * @file PIDController.c
 * @author Dhairya Gupta
 * @brief Implementation for PID controllers.
 * @version 0.1
 * @date 2025-04-17
 */

#include "../../inc/util/PIDController.h"

#include <math.h>  // For fabs, potentially other math functions if needed
#include <stddef.h>

// Define a small epsilon for floating point comparisons, especially for dt
#define FLOAT_EPSILON 1e-6

/**
 * @brief Initializes the PIDController struct with gains and limits.
 *
 * @param pid Pointer to the PIDController struct to initialize.
 * @param kp Proportional gain.
 * @param ki Integral gain.
 * @param kd Derivative gain.
 * @param maxOutput Maximum output limit.
 * @param minOutput Minimum output limit.
 * @param integralLimit Maximum absolute value for the integral term
 * (anti-windup). Set to 0 or negative for no limit.
 * @param derivativeLimit Maximum absolute value for the derivative term.
 * Set to 0 or negative for no limit.
 * @param integralResetLimit Threshold for error change to potentially reset
 * integral (specific reset logic depends on application). Set to 0 or negative
 * if not used.
 */
void PIDController_init(PIDController *pid, float kp, float ki, float kd,
                        float maxOutput, float minOutput, float integralLimit,
                        float derivativeLimit, float integralResetLimit) {
    if (pid == NULL) {
        return;
    }

    // update the gain parameters
    pid->_kp = kp;
    pid->_ki = ki;
    pid->_kd = kd;

    if (maxOutput >= minOutput) {
        pid->_maxOutput = maxOutput;
        pid->_minOutput = minOutput;
    } else {
        // just in case
        pid->_maxOutput = fmaxf(maxOutput, minOutput);
        pid->_minOutput = fminf(maxOutput, minOutput);
    }

    pid->_integralLimit = (integralLimit > 0)
                              ? integralLimit
                              : -1.0f;  // Use -1 to indicate no limit
    pid->_derivativeLimit = (derivativeLimit > 0)
                                ? derivativeLimit
                                : -1.0f;  // Use -1 to indicate no limit
    pid->_integralResetLimit = integralResetLimit;  // Store as is

    // Initialize internal states
    pid->_setpoint = 0.0f;
    pid->_error = 0.0f;
    pid->_integral = 0.0f;
    pid->_derivative = 0.0f;
    pid->_prevError = 0.0f;
    pid->output = 0.0f;
}

/**
 * @brief Calculates the PID controller output based on the current value and a
 * new setpoint. Updates the internal setpoint of the controller.
 *
 * @param pid Pointer to the PIDController struct.
 * @param currentValue The current measured value from the process/sensor.
 * @param newSetpoint The desired target value (setpoint) for this cycle.
 * @param dt Time delta in seconds since the last call.
 * @return The calculated PID output, clamped within the min/max limits.
 */
float PIDController_evaluate(PIDController *pid, float currentValue,
                             float newSetpoint, float dt) {
    if (pid == NULL || dt <= FLOAT_EPSILON) {
        // just in case
        return (pid != NULL) ? pid->output : 0.0f;
    }

    pid->_setpoint = newSetpoint;

    pid->_error = pid->_setpoint - currentValue;

    float p_term = pid->_kp * pid->_error;

    pid->_integral += pid->_error * dt;

    // Apply integral windup limit (anti-windup)
    if (pid->_integralLimit > 0) {
        if (pid->_integral > pid->_integralLimit) {
            pid->_integral = pid->_integralLimit;
        } else if (pid->_integral < -pid->_integralLimit) {
            pid->_integral = -pid->_integralLimit;
        }
    }

    // TODO: INTEGRAL RESET LOGIC

    float i_term = pid->_ki * pid->_integral;

    // Calculate derivative
    pid->_derivative = (pid->_error - pid->_prevError) / dt;

    float d_term = pid->_kd * pid->_derivative;

    // New output
    pid->output = p_term + i_term + d_term;

    // Make sure output is not higher -- basically limit it to the limits
    if (pid->output > pid->_maxOutput) {
        pid->output = pid->_maxOutput;
    } else if (pid->output < pid->_minOutput) {
        pid->output = pid->_minOutput;
    }

    pid->_prevError = pid->_error;

    return pid->output;
}