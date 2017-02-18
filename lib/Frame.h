#include <Arduino.h>
#include "trajectories.h"
#ifndef frame_h
#define frame_h

class Frame {

    private:
      int *positions;
    public:
      int upper_pos_rf;
      int lower_pos_rf;
      int upper_pos_lb;
      int lower_pos_lb;
      int upper_pos_rb;
      int lower_pos_rb;
      int upper_pos_lf;
      int lower_pos_lf;

      Frame(int* location);
      Frame(int value);
      Frame get_frame(Frame* frame);
      int is_null();
      void print();
};

#endif
