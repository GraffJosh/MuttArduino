#include <Arduino.h>
#ifndef frame_h
#define frame_h

class Frame {

    private:
      int positions[8];
        int upper_pos_rb = positions[0];
        int upper_pos_lb = positions[1];
        int upper_pos_lf = positions[2];
        int upper_pos_rf = positions[3];

        int lower_pos_rb = positions[4];
        int lower_pos_lb = positions[5];
        int lower_pos_lf = positions[6];
        int lower_pos_rf = positions[7];


    public:
      Frame(int,int,int,int,int,int,int,int);
};

#endif
