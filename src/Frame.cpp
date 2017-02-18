#include "../lib/Frame.h"


Frame::Frame(int upper_pos_rb_var, int upper_pos_lb_var, int upper_pos_lf_var, int upper_pos_rf_var, int lower_pos_rb_var,
        int lower_pos_lb_var,
        int lower_pos_lf_var,
        int lower_pos_rf_var){

    positions[0] = upper_pos_rb_var;
    positions[1] = upper_pos_lb_var;
    positions[2] = upper_pos_lf_var;
    positions[3] = upper_pos_rf_var;

    positions[4] = lower_pos_rb_var;
    positions[5] = lower_pos_lb_var;
    positions[6] = lower_pos_lf_var;
    positions[7] = lower_pos_rf_var;

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
