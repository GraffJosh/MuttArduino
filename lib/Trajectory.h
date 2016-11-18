#ifndef Trajectory_h
#define Trajectory_h
#include "Leg.h"
#include <Arduino.h>


#define TRAJ_LENGTH 25
class Leg;

struct Frame {
  Leg *leg1;
  double leg_pos;
  bool solenoid;
};

class Trajectory
{
private:
  int curr_time=0,curr_index=0;
  Frame sequence[TRAJ_LENGTH];
public:
  Trajectory();
  int send_trajectory();
  void push_back(Leg *leg1, double leg_pos, bool solenoid);
  void push_back(Frame *new_frame, int new_time);
  int insert_frame(Leg *leg1, double leg_pos, bool solenoid, int new_time);

};


#endif
