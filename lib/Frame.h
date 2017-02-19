#include <Arduino.h>
#include <avr/pgmspace.h>
#include "trajectories.h"
#ifndef frame_h
#define frame_h

class Frame {

    private:
    public:
      const int *remote_positions;
      int *local_positions;
      Frame();
      Frame(const int* location);
      Frame(int* location);
      Frame(int value);
      int get_frame(Frame* ret_frame);
      int is_null();
      void print();
      void print_local();
};

#endif
