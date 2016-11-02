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
	double set_position(double angle);
	double get_positon();
	void drive();
	void update_position();
};

#endif
