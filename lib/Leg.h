#ifndef leg_h
#define leg_h

#include "../lib/I2CEncoder/I2CEncoder.h"
#include "../lib/PID/PID_v1.h"
#include "../lib/SoftwareServo/SoftwareServo.h"
#include "Trajectory.h"
#include <Arduino.h>
void setup_encoders();

class Trajectory;

class Leg
{
private:
	I2CEncoder encoder;
	SoftwareServo servo;
	PID pos_pid;
	PID frc_pid;
	double set_pos, curr_pos, cmd_pos, pos_Kp, pos_Ki, pos_Kd;
	double set_frc, curr_frc, cmd_frc, frc_Kp, frc_Ki, frc_Kd;
	double max_angle_converted, min_angle_converted;
	int fwd_chnl,rvs_chnl, max_angle,min_angle;
	int frc_chnl, max_frc, min_frc;
	int servo_chnl;
public:
	Leg();
	int send_trajectory(int step, Trajectory traj);
	int zero();
	double set_position(double angle);
	int set_servo(int servo);
	double get_position();
	int get_position_cmd();
	double set_force(double frc);
	double get_force();
	int get_force_cmd();
	void drive();
	void set_sample_freq(int sample_freq);
	void drive(int cmd);
	void update_position();
	void update_force();
};

#endif
