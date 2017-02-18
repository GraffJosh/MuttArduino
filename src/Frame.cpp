#include "../lib/Frame.h"

Frame::Frame()
{

}
Frame::Frame(int* frame_location){
    local_positions = frame_location;
  }
//FR_Upper FR_Lower BL_Upper BL_Lower BR_Upper BR_Lower FL_Upper FL_Lower
Frame::Frame(const int* frame_location){
    remote_positions = frame_location;
}

// Frame::Frame(int value)
// {
//   remote_positions = (int*)malloc(sizeof(int)*8);
//   for(int i=0;i<8;i++)
//   {
//     remote_positions[i] = 4200;
//   }
// }

//sets the "local_positions" of *ret_frame to be the values in flash of *this
//returns 1 on success, 0 on failure
int Frame::get_frame(Frame* ret_frame)
{
  if(this->is_null())
  {return 0;}
  for(int i=0;i<8;i++)
  {
    ret_frame->local_positions[i] = pgm_read_word_near(remote_positions[i]);
  }
  return 1;
}

//returns 0 if the frame is an endpoint of a framelist
int Frame::is_null()
{
  if(remote_positions[0]==4200)
  {
    return 0;
  }else{
    return 1;
  }
}

void Frame::print()
{
  Serial.print("frame: ");
  Serial.print((int)pgm_read_word_near(remote_positions));
  Serial.print(", ");
  Serial.print((int)pgm_read_word_near(remote_positions+1));
  Serial.print(", ");
  Serial.print((int)pgm_read_word_near(remote_positions+2));
  Serial.print(", ");
  Serial.print((int)pgm_read_word_near(remote_positions+3));
  Serial.print(", ");
  Serial.print((int)pgm_read_word_near(remote_positions+4));
  Serial.print(", ");
  Serial.print((int)pgm_read_word_near(remote_positions+5));
  Serial.print(", ");
  Serial.print((int)pgm_read_word_near(remote_positions+6));
  Serial.print(", ");
  Serial.println((int)pgm_read_word_near(remote_positions+7));
}
