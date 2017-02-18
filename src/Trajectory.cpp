#include "../lib/Trajectory.h"
#include "../lib/Leg.h"


Trajectory::Trajectory(int list_size,const int list_location[][8])
{

  frame_list = (Frame**)malloc(sizeof(Frame*)*(list_size));
  build_list(list_size, list_location);

}

Trajectory::Trajectory(int list_size)
{
  frame_list = (Frame**)malloc(sizeof(Frame*)*(list_size));
}

void Trajectory::add_list(int list_size, int list_location[][8])
{
  frame_list = (Frame**)malloc(sizeof(Frame*)*(list_size));
  if(frame_list == NULL)
  {
    Serial.println("FATAL ERROR::MALLOC");
  }
  build_list(list_size, list_location);
}

void Trajectory::build_list(int list_size,const int list_location[][8])
{
Serial.print("build list of size: ");
Serial.println(list_size);

  for(int i=0;i<list_size;i++)
  {
      Frame* newFrame = new Frame(list_location[i]);
      if(newFrame == NULL)
      {Serial.println("fuck\n" );}
      frame_list[i] = newFrame;
      newFrame->print();
  }

}

//returns 1 on success, 0 on failure
int Trajectory::get_frame(int curr_time,Frame* ret_frame)
{
  return frame_list[curr_time]->get_frame(ret_frame);
}
