#include "../lib/Trajectory.h"
#include "../lib/Leg.h"

Frame walk_1[0] = {};
Trajectory::Trajectory(int n, Frame* trajFrameList)
{
	// curr_index = 0;
	// curr_time = 0;

size = n+1;
Frame frameList[size];
frameList = trajFrameList;
frameList[size] = Frame(0,0,0,0,0,0,0,0);

}


//adds trajectory to the list of trajectories to be executed
// int Trajectory::send_trajectory(int curr_time)
// {
// 	Frame *curr_frame = get_frame(curr_time%TRAJ_LENGTH);
// 	curr_frame->leg1->set_position(curr_frame->leg_pos);
// 	curr_frame->leg1->set_servo((int)curr_frame->solenoid);
//
//   return curr_time;
// }

// Frame* Trajectory::get_frame(int time_step)
// {
// 	return sequence+(time_step*sizeof(Frame));
// }

//add a frame to the end of a Trajectory/
//stub
// int Trajectory::push_back(Frame *new_frame, int num_frames)
// {
// 	return -1;
// }


//add a frame to the end of a trajectory
// int Trajectory::push_back(Leg *leg1, double leg_pos, bool solenoid)
// {
// 	if(curr_index<TRAJ_LENGTH)
// 	{
// 	  Frame *new_frame = sequence+(curr_index*sizeof(Frame));
// 	  new_frame->leg1 = leg1;
// 	  new_frame->leg_pos = leg_pos;
// 	  new_frame->solenoid = solenoid;
// 		++curr_index;
// 		return curr_index;
// 	}else{
// 		return -1;
// 	}
// }


//inserts a frame into the middle of a trajectory
// int Trajectory::insert_frame(Leg *leg1, double leg_pos, bool solenoid, int new_time)
// {
//   if(new_time<=curr_index)
//   {
//     Frame *new_frame = sequence+(new_time*sizeof(Frame));
//     new_frame->leg1 = leg1;
//     new_frame->leg_pos = leg_pos;
//     new_frame->solenoid = solenoid;
//   }
//
//   return new_time;
// }


//appends a motion to the trajectory
// int Trajectory::plan_motion(Leg *leg, double start_angle, double end_angle, int time_period)
// {
// 	int step=0,angle=0;
// 	bool solenoid;
// 	if(curr_index+time_period < TRAJ_LENGTH)
// 	{
// 		step = (end_angle-start_angle)/time_period;
// 		angle = start_angle;
// 		for(int i=0;i<time_period;i++)
// 		{
// 			solenoid = (angle > SOLENOID_TOP)&&(step>SOLENOID_STEP) ? true:false;
// 			push_back(leg, start_angle+step,solenoid);
// 			angle += step;
// 		}
// 	}
// 	return curr_index;
// }
