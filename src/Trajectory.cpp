#include "../lib/Trajectory.h"
#include "../lib/Leg.h"

Trajectory::Trajectory(void)
{

}

int Trajectory::send_trajectory()
{

  return curr_time;
}

void Trajectory::push_back(Frame *new_frame, int new_time)
{


}

void Trajectory::push_back(Leg *leg1, double leg_pos, bool solenoid)
{
  Frame *new_frame = sequence+(curr_index*sizeof(Frame));
  new_frame->leg1 = leg1;
  new_frame->leg_pos = leg_pos;
  new_frame->solenoid = solenoid;
}

int Trajectory::insert_frame(Leg *leg1, double leg_pos, bool solenoid, int new_time)
{
  if(new_time<=curr_index)
  {
    Frame *new_frame = sequence+(new_time*sizeof(Frame));
    new_frame->leg1 = leg1;
    new_frame->leg_pos = leg_pos;
    new_frame->solenoid = solenoid;
  }

  return new_time;
}
