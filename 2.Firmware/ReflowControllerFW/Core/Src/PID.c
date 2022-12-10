#include "PID.h"

void PIDController_Init(PIDController *pid){

	//clear controller variables
	pid->integrator = 0.0f;
	pid->prevError = 0.0f;
	pid->differentiator = 0.0f;
	pid->prevMeasurement = 0.0f;
	pid->out = 0.0f;
}


float PIDController_Update(PIDController *pid, float setpoint, float measurement){
	//error signal
	float error = setpoint - measurement;

	//proportional
	float proportional = pid->Kp * error;

	//integral
	pid->integrator = pid->integrator + 0.5f * pid->Ki * pid->T * (error + pid->prevError);

	//anti-wind-up via dynamic integrator clamping
    if (pid->integrator > pid->limMaxInt) {

        pid->integrator = pid->limMaxInt;

    } else if (pid->integrator < pid->limMinInt) {

        pid->integrator = pid->limMinInt;

    }

    //derivative
    pid->differentiator = -(2.0f * pid->Kd * (measurement - pid->prevMeasurement)	/* Note: derivative on measurement, therefore minus sign in front of equation! */
                        + (2.0f * pid->tau - pid->T) * pid->differentiator)
                        / (2.0f * pid->tau + pid->T);


    //compute output
    pid->out = proportional + pid->integrator + pid->differentiator;

    //constrain output
    if (pid->out > pid->limMax) {

        pid->out = pid->limMax;

    } else if (pid->out < pid->limMin) {

        pid->out = pid->limMin;

    }

	// Store error and measurement for later use
    pid->prevError       = error;
    pid->prevMeasurement = measurement;

	// Return controller output
    return pid->out;

}
