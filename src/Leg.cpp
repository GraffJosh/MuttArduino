#include "../lib/Leg.h"
//#include "../lib/SoftwareServo/SoftwareServo.h"
#include "../lib/Servo/src/Servo.h"
#include "../lib/PID/PID_v1.h"
#include "../lib/Trajectory.h"
Leg::Leg(int fwd_chnl_pin,int rvs_chnl_pin,int servo_chnl_pin,int frc_chnl_pin, int is_left)
: encoder()
, pos_pid(&curr_pos, &cmd_pos, &set_pos, pos_Kp, pos_Ki, pos_Kd,DIRECT)
, frc_pid(&curr_frc, &cmd_frc, &set_frc, frc_Kp, frc_Ki, frc_Kd,DIRECT)
{
	set_pos = 0;
	curr_pos = 0;
	cmd_pos = 0;
	pos_Kp = 1300; //3500
	pos_Ki = 200;
	pos_Kd = 20;//10;
	set_frc = 0;
	curr_frc = 0;
	cmd_frc = 0;
	frc_Kp = 40;
	frc_Ki = 12;
	frc_Kd = .1;
	frc_chnl = frc_chnl_pin;
	fwd_chnl = fwd_chnl_pin;
	rvs_chnl = rvs_chnl_pin;
	max_angle=360;
	min_angle = 0;
	max_frc=150;
	min_frc = 0;
	left = is_left;

	servo_chnl = servo_chnl_pin;

	pinMode(frc_chnl,INPUT);
	pinMode(fwd_chnl,OUTPUT);
	pinMode(rvs_chnl,OUTPUT);
	pinMode(servo_chnl,OUTPUT);
	pos_pid.SetTunings(pos_Kp,pos_Ki,pos_Kd);
	pos_pid.SetMode(AUTOMATIC);
	pos_pid.SetOutputLimits(-500,500);
	// frc_pid.SetTunings(pos_Kp,pos_Ki,pos_Kd);
	// frc_pid.SetMode(AUTOMATIC);
	// frc_pid.SetOutputLimits(-250,250);
	servo.attach(servo_chnl);
	motor.attach(fwd_chnl);


}

void Leg::get_info(){

	Serial.println("Printing servo of leg");
	Serial.println(servo_chnl);
}

int Leg::send_trajectory(Trajectory traj)
{
	return 0;
}

void Leg::init_leg_encoder(){

	encoder.init(MOTOR_393_SPEED_ROTATIONS, MOTOR_393_TIME_DELTA);
	zero();

}

double Leg::get_encoder_position()
{
	return encoder.getPosition();
}

//zeroes the leg using the force sensor.
//returns zero on success.
int Leg::zero()
{
	for(int i=0;i<200;i++)
	{
		drive(1650);
		delay(15);
		i++;
		// Serial.print(", zero force: ");
		// update_force();
	}
	set_servo(0);
	encoder.zero();
	return 0;
}


//ask the leg to go to a position 0->360
double Leg::set_position(double angle)
{

	// Serial.print("angle: ");
	// Serial.print(angle);
	if(angle > max_angle)
	{
		angle = max_angle;
	}else if(angle < min_angle)
	{
		angle = min_angle;
	}
	//angle = mapdouble(angle, min_angle,max_angle,min_angle_converted,max_angle_converted);
	if(left)
	{
		angle = 1*angle/120;
	}else{
		angle = -1*angle/120;
	}
	set_pos = angle;
	return set_pos;
}

//ask the leg to go to a position 0->360
double Leg::set_position(double angle, int servo_angle)
{

	// Serial.print("angle: ");
	// Serial.print(angle);
	if(angle > max_angle)
	{
		angle = max_angle;
	}else if(angle < min_angle)
	{
		angle = min_angle;
	}
	//angle = mapdouble(angle, min_angle,max_angle,min_angle_converted,max_angle_converted);
	if(left)
	{
		angle = 1*angle/120;
	}else{
		angle = -1*angle/120;
	}
	set_pos = angle;
	set_servo(servo_angle);
	return set_pos;
}

double Leg::get_position()
{
	return curr_pos;
}
int Leg::get_position_cmd()
{
	return cmd_pos;
}

int Leg::set_servo(int pos)
{
	if(left)
	{
	pos = map(pos,0,180,170,-10);
	servo.write(pos);
	}else{
		pos = map(pos,0,180,-10,170);
		servo.write(pos);
	}
	return pos;
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
//ie. 2000 is full fwd, 1000 full rvs
void Leg::drive(int cmd)
{
	motor.writeMicroseconds(cmd);
}

// drives the motor to the cmd_pos as defined by the PID structure
void Leg::drive()
{
	if(left)
	{
		motor.writeMicroseconds(1500-cmd_pos);
	}else{
		motor.writeMicroseconds(cmd_pos+1500);
	}
}


void Leg::set_sample_freq(int sample_freq)
{
	pos_pid.SetSampleTime(sample_freq/1000);
}


//updates the position and computes PID.
//WARNING. EXECUTED DURING INTERRUPT. DO NOT CHANGE.
void Leg::update_position()
{
	curr_pos = encoder.getPosition();
	pos_pid.Compute();
	// servo.refresh();
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
