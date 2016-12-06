#ifndef Trajectory_h
#define Trajectory_h
#include "Leg.h"
#include <Arduino.h>


#define TRAJ_LENGTH 500
#define SOLENOID_TOP 70 //angle after which to use servo
#define SOLENOID_STEP 15 //angles per time to trigger servo

class Leg;

typedef struct _Frame {
  Leg *leg1;
  double leg_pos;
  bool solenoid;
} Frame;

class Trajectory
{
private:
  int curr_time,curr_index;
  Frame sequence[TRAJ_LENGTH];
public:
  Trajectory();
  int send_trajectory(int curr_time);
	Frame* get_frame(int curr_time);
  int push_back(Leg *leg1, double leg_pos, bool servo);
  int push_back(Frame *new_frame, int num_frames);
  int insert_frame(Leg *leg1, double leg_pos, bool servo, int new_time);
	int plan_motion(Leg *leg, double start_angle, double end_angle, int time_period);

};


#endif
