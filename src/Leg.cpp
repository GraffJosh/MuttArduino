#include "../lib/Leg.h"
#include "../lib/PID/PID_v1.h"

Leg::Leg(void)
: encoder()
, pid(&curr_pos, &cmd_signal, &set_pos, Kp, Ki, Kd, DIRECT)
{
	set_pos = 0;
	curr_pos = 0;
	cmd_signal = 0;
	Kp = 0;
	Ki = 0;
	Kd = 0;

	pid.SetTunings(Kp,Ki,Kd);
	encoder.init(MOTOR_393_SPEED_ROTATIONS, MOTOR_393_TIME_DELTA);
	encoder.zero();
}


int Leg::set_position(int angle)
{

	set_pos = (double) angle;

	return angle;
}

//send PWM to motor controller
void Leg::drive()
{
	analogWrite(pwm_channel,cmd_signal);
}



//updates the position and computes PID.
//WARNING. EXECUTED DURING INTERRUPT. DO NOT CHANGE.
void Leg::update_position()
{
	curr_pos = encoder.getPosition();
	pid.Compute();
}
