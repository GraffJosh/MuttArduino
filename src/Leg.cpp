#include "../lib/Leg.h"
#include "../lib/PID/PID_v1.h"

Leg::Leg(void)
: encoder()
, pos_pid(&curr_pos, &cmd_pos, &set_pos, pos_Kp, pos_Ki, pos_Kd, REVERSE)
, frc_pid(&curr_frc, &cmd_frc, &set_frc, frc_Kp, frc_Ki, frc_Kd, REVERSE)
{
	set_pos = 0;
	curr_pos = 0;
	cmd_pos = 0;
	pos_Kp = 300;
	pos_Ki = 200;
	pos_Kd = 30;
	set_frc = 0;
	curr_frc = 0;
	cmd_frc = 0;
	frc_Kp = 40;
	frc_Ki = 12;
	frc_Kd = .1;

	frc_chnl = A2;
	fwd_chnl = 10;
	rvs_chnl = 9;
	max_angle=180;
	min_angle = 0;
	max_frc=250;
	min_frc = 0;


	pinMode(frc_chnl,INPUT);
	pinMode(fwd_chnl,OUTPUT);
	pinMode(rvs_chnl,OUTPUT);
	pos_pid.SetTunings(pos_Kp,pos_Ki,pos_Kd);
	pos_pid.SetMode(AUTOMATIC);
	pos_pid.SetOutputLimits(-250,250);
	frc_pid.SetTunings(pos_Kp,pos_Ki,pos_Kd);
	frc_pid.SetMode(AUTOMATIC);
	frc_pid.SetOutputLimits(-250,250);

	encoder.init(MOTOR_393_SPEED_ROTATIONS, MOTOR_393_TIME_DELTA);
	zero();
}


int Leg::send_trajectory(int step, Trajectory traj)
{


	return 0;
}



//zeroes the leg using the force sensor.
//returns zero on success.
int Leg::zero()
{
	while(get_force()<max_frc)
	{
		drive(-80);
		Serial.print("zero force: ");
		Serial.println(get_force());
		update_force();
	}
	encoder.zero();
	return 0;
}


//ask the leg to go to a position
double Leg::set_position(double angle)
{

	Serial.print("angle: ");
	Serial.print(angle);
	if(angle > max_angle)
	{
		angle = max_angle;
	}else if(angle < min_angle)
	{
		angle = min_angle;
	}
	//angle = mapdouble(angle, min_angle,max_angle,min_angle_converted,max_angle_converted);
	angle = -1*angle/120;
	Serial.print("angle: ");
	Serial.print(angle);
	set_pos = angle;
	return angle;
}
double Leg::get_position()
{
	return curr_pos;
}
int Leg::get_position_cmd()
{
	return cmd_pos;
}





//ask the leg to go to a force
double Leg::set_force(double frc)
{
	if(frc > min_frc)
	{
		frc = max_frc;
	}else if(frc < min_frc)
	{
		frc = min_frc;
	}
	Serial.print("frc: ");
	Serial.print(frc);
	set_frc = frc;
	return frc;
}
double Leg::get_force()
{
	return curr_frc;
}
int Leg::get_force_cmd()
{
	return cmd_frc;
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
	pos_pid.SetSampleTime(1/sample_freq);
}


//updates the position and computes PID.
//WARNING. EXECUTED DURING INTERRUPT. DO NOT CHANGE.
void Leg::update_position()
{
	curr_pos = encoder.getPosition();
	pos_pid.Compute();
	// Serial.print(curr_pos);
	// Serial.print("    ");
}
//updates the position and computes PID.
//WARNING. EXECUTED DURING INTERRUPT. DO NOT CHANGE.
void Leg::update_force()
{
  curr_frc = analogRead(frc_chnl);
	frc_pid.Compute();
	// Serial.print(curr_pos);
	// Serial.print("    ");
}
