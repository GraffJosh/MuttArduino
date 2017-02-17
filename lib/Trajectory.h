#ifndef Trajectory_h
#define Trajectory_h
#include "Frame.h"
#include <Arduino.h>

class Frame;

class Trajectory
{
private:
  //int curr_time,curr_index;
  //Frame sequence[TRAJ_LENGTH];
  int size;
  Frame* frameList;
  Frame endFrame;

public:
  Trajectory(int size, Frame* frameList);

  // int send_trajectory(int curr_time);
	// Frame* get_frame(int curr_time);
  // int push_back(Leg *leg1, double leg_pos, bool servo);
  // int push_back(Frame *new_frame, int num_frames);
  // int insert_frame(Leg *leg1, double leg_pos, bool servo, int new_time);
	// int plan_motion(Leg *leg, double start_angle, double end_angle, int time_period);

};


#endif
