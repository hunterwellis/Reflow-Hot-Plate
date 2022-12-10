#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

typedef struct {

	//controller gain
	float Kp;
	float Ki;
	float Kd;

	//derivative low-pass filter time constant
	float tau;

	//output limits
	float limMin;
	float limMax;

	//integrator limits
	float limMinInt;
	float limMaxInt;

	//sample time
	float T;

	//controller memory
	float integrator;
	float prevError;
	float differentiator;
	float prevMeasurement;

	//controller output
	float out;

} PIDController;

void PIDController_Init(PIDController *pid);
float PIDController_Update(PIDController *pid, float setpoint, float measurement);


#endif
