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
  Frame* frame_list;
  void build_list(int list_size,int list_location[][8], Frame* list_return);
public:
  //constructor.
  //Size of the Trajectory
  //pointer to the list of integers for the positions
    //the list is 100x8
  Trajectory(int size, int trajFrameList[][8]);
  Trajectory();


  void add_list(int n, int list_location[][8]);
};


#endif
