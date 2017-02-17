#include <Arduino.h>
#ifndef frame_h
#define frame_h

class Frame {

    private:

        int upper_pos_rb;
        int upper_pos_lb;
        int upper_pos_lf;
        int upper_pos_rf;



        int lower_pos_rb;
        int lower_pos_lb;
        int lower_pos_lf;
        int lower_pos_rf;


    public:
      Frame(int,int,int,int,int,int,int,int);
};

#endif
