#include "../lib/Leg.h"
#include "../lib/PID/PID_v1.h"

Leg::Leg(void)
: encoder()
, pid(&curr_pos, &cmd_signal, &set_pos, Kp, Ki, Kd, DIRECT)
{
	set_pos = 0;
	curr_pos = 0;
	cmd_signal = 0;
	Kp = 1;
	Ki = 0;
	Kd = 0;
	pwm_channel =7;
	pinMode(pwm_channel,OUTPUT);
	pid.SetTunings(Kp,Ki,Kd);
	pid.SetMode(AUTOMATIC);
	pid.SetOutputLimits(170,250);
	encoder.init(MOTOR_393_SPEED_ROTATIONS, MOTOR_393_TIME_DELTA);
	encoder.zero();
}

//ask the leg to go to a position
double Leg::set_position(double angle)
{
	set_pos =  angle;
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
void Leg::drive(int cmd)
{
	Serial.println(cmd);
	analogWrite(pwm_channel,cmd);
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
	//pid.Compute();

}
