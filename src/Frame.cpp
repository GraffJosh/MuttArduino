#include "../lib/Frame.h"

//FR_Upper FR_Lower BL_Upper BL_Lower BR_Upper BR_Lower FL_Upper FL_Lower
Frame::Frame(int* frame_location){
    positions = frame_location;
    // positions[0] = upper_pos_rb_var;
    // positions[1] = upper_pos_lb_var;
    // positions[2] = upper_pos_lf_var;
    // positions[3] = upper_pos_rf_var;

    // positions[4] = lower_pos_rb_var;
    // positions[5] = lower_pos_lb_var;
    // positions[6] = lower_pos_lf_var;
    // positions[7] = lower_pos_rf_var;
}

// Frame::Frame(int value)
// {
//   positions = (int*)malloc(sizeof(int)*8);
//   for(int i=0;i<8;i++)
//   {
//     positions[i] = 4200;
//   }
// }


//returns 1 on success, 0 on failure
int get_frame(Frame* desired_frame,Frame* ret_frame)
{
  ret_frame->upper_pos_rf = pgm_read_word_near(desired_frame+0);
  ret_frame->lower_pos_rf = pgm_read_word_near(desired_frame+1);
  ret_frame->upper_pos_lb = pgm_read_word_near(desired_frame+2);
  ret_frame->lower_pos_lb = pgm_read_word_near(desired_frame+3);
  ret_frame->upper_pos_rb = pgm_read_word_near(desired_frame+4);
  ret_frame->lower_pos_rb = pgm_read_word_near(desired_frame+5);
  ret_frame->upper_pos_lf = pgm_read_word_near(desired_frame+6);
  ret_frame->lower_pos_lf = pgm_read_word_near(desired_frame+7);
  return 1;
}

int Frame::is_null()
{
  if(positions[0]==4200)
  {
    return 0;
  }else{
    return 1;
  }
}

void Frame::print()
{
  Serial.print("frame: ");
  Serial.print(positions[0]);
  Serial.print(", ");
  Serial.print(positions[2]);
  Serial.print(", ");
  Serial.print(positions[4]);
  Serial.print(", ");
  Serial.println(positions[6]);
}
