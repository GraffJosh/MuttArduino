#include "../lib/Leg.h"
#include "../lib/PID/PID_v1.h"

Leg::Leg(void)
: encoder()
, pid(&curr_pos, &cmd_signal, &set_pos, Kp, Ki, Kd, REVERSE)
{
	set_pos = 0;
	curr_pos = 0;
	cmd_signal = 0;
	Kp = 40;
	Ki = 12;
	Kd = .1;
	fwd_chnl = 10;
	rvs_chnl = 9;
	max_angle=90;
	min_angle = 0;
	max_angle_converted = max_angle/360;
	min_angle_converted = min_angle/360;
	pinMode(fwd_chnl,OUTPUT);
	pinMode(rvs_chnl,OUTPUT);
	pid.SetTunings(Kp,Ki,Kd);
	pid.SetMode(AUTOMATIC);
	pid.SetOutputLimits(-250,250);
	encoder.init(MOTOR_393_SPEED_ROTATIONS, MOTOR_393_TIME_DELTA);
	encoder.zero();
}

//ask the leg to go to a position
double Leg::set_position(double angle)
{
	if(angle > min_angle)
	{
		angle = max_angle;
	}else if(angle < min_angle)
	{
		angle = min_angle;
	}
	angle = map(angle, min_angle,max_angle,min_angle_converted,max_angle_converted);
	Serial.print("angle:");
	Serial.print(angle);
	set_pos = angle;
	return angle;
}

double Leg::get_positon()
{
	return curr_pos;
}

int Leg::get_cmd()
{
	return cmd_signal;
}

//send PWM to motor controller
//255 appears to be full in that direction.
//ie. +255 is full fwd, -255 full rvs
void Leg::drive(int cmd)
{
	if(cmd > 0)
	{
		analogWrite(fwd_chnl,cmd);
		digitalWrite(rvs_chnl,0);
	}
	else if(cmd<0)
	{
		analogWrite(rvs_chnl,-1*cmd);
		digitalWrite(fwd_chnl,0);
	}
}

void Leg::set_sample_freq(int sample_freq)
{
	pid.SetSampleTime(1/sample_freq);
}


//updates the position and computes PID.
//WARNING. EXECUTED DURING INTERRUPT. DO NOT CHANGE.
void Leg::update_position()
{
	curr_pos = encoder.getPosition();
	pid.Compute();
	// Serial.print(curr_pos);
	// Serial.print("    ");
}
