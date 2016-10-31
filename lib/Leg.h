#ifndef leg_h
#define leg_h

#include "../lib/I2CEncoder/I2CEncoder.h"
#include "../lib/PID/PID_v1.h"
#include <Arduino.h>
void setup_encoders();


class Leg
{
private:
	I2CEncoder encoder;
	PID pid;
	double set_pos, curr_pos, cmd_signal, Kp, Ki, Kd;
	int pwm_channel;
public:
	Leg();
	int set_position(int angle);
	void set_sample_freq(int sample_freq);
	int get_position();
	int get_cmd();
	void drive(int cmd);
	void update_position();
};

#endif
