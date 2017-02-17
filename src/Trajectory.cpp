#include "../lib/Trajectory.h"
#include "../lib/Leg.h"


Trajectory::Trajectory(int n, int list_location[][8])
{

  size = n+1;
  build_list(size, list_location, frame_list);

}

Trajectory::Trajectory()
{

}

void Trajectory::add_list(int n, int list_location[][8])
{
  frame_list = (Frame*)malloc(sizeof(Frame)*(n+1));
  size = n+1;
  build_list(n, list_location, frame_list);
}

void Trajectory::build_list(int list_size,int list_location[][8], Frame* list_return)
{

  for(int i=0;i<list_size-1 ;i++)
  {
    list_return[i] = Frame(list_location[i][0],list_location[i][1],
      list_location[i][2],list_location[i][3],
      list_location[i][4],list_location[i][5],
      list_location[i][6],list_location[i][7]);
  }
  frame_list[size] = Frame(0,0,0,0,0,0,0,0);
}
