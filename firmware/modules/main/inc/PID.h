#ifndef _MAIN_PID_H
#define _MAIN_PID_H

/*
  external library: https://github.com/pms67/PID
 */

typedef struct {

    /* Controller gains */
    float Kp;
    float Ki;
    float Kd;

    /* Derivative low-pass filter time constant */
    float tau;

    /* Output limits */
    float limMin;
    float limMax;

    /* Integrator limits */
    float limMinInt;
    float limMaxInt;

    /* Sample time (in seconds) */
    float T;

    /* Controller "memory" */
    float integrator;
    float prevError; /* Required for integrator */
    float differentiator;
    float prevMeasurement; /* Required for differentiator */

    /* Controller output */
    float out;

} PIDController;

void PIDController_Init(PIDController* pid);
float PIDController_Update(PIDController* pid, float setpoint, float measurement);

#endif
