

#define due 0
#define timingpin 52
#include <Wire.h>
#include <Arduino.h>
#include "../lib/motor_control.h"
#include "../lib/Leg.h"
#include "../lib/Trajectory.h"
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#define __AVR_ATmega2560__ 1
#include <avr/io.h>
//#include "../lib/DueTimer/DueTimer.h"
#include "../lib/Servo/src/Servo.h"
#include "../gait_1.h"
#include "../gait_2.h"
#include "../gait_3.h"
#include "../gait_4.h"
#include "../gait_5.h"
#include <TimerOne.h>
#if due == 0
#endif

int traj_time = 0,traj_period=2,traj_loaded=0;
Trajectory* current_trajectory;
Trajectory* simple;
Trajectory* trot;
Trajectory* servo_test;
Trajectory* single_step;
Trajectory* biped;
Frame* curr_frame;

//Leg declarations
Leg *lb_leg;
Leg *rb_leg;
Leg *lf_leg;
Leg *rf_leg;
Servo servoMotor;
int ByteReceived;
int drive = 0,upper_pos_pot=A0, lower_pos_pot=A1;
int servo_pos = 0;
int sample_period;
int legs_initialized = 0;
volatile int print = 1,curr_time = 0;
//left back motor declarations
int left_back_fwd = 8; //10;
int left_back_rvs = 6; //4;
int left_back_servo = 32;
int left_back_force = A8;

//right back motor declarations
int right_back_fwd = 2; //3;
int right_back_rvs = 3; //2;
int right_back_servo = 30;
int right_back_force = A11;

//left forward motor declarations
int left_forward_fwd = 5; //9;
int left_forward_rvs = 4; //8;
int left_forward_servo = 36;
int left_forward_force = A9;

//right forward motor declarations
int right_forward_fwd = 9; //6;
int right_forward_rvs = 10; //5;
int right_forward_servo = 34;
int right_forward_force = A10;


// #if due == 1
// //TC1 ch 0
// ISR(TIMER1_COMPA_vect)
// {
//   #if due == 1
//     TC_GetStatus(TC1, 0);
//   #endif
//   print = 1;
// }
// #else
void timerIsr()
{

  if(legs_initialized)
  {
     print = 1;
  }
  if(traj_loaded)
  {
    ++curr_time;
  }
}
// #endif
//home position
void home()
{
  rf_leg->set_position(0,60);
  lf_leg->set_position(0,60);
  rb_leg->set_position(100,90);
  lb_leg->set_position(100,90);
}
//this is just to stand
void stand()
{
  rf_leg->set_position(210,90);
  lf_leg->set_position(210,90);
  //rb_leg->set_position(190,90);
  //lb_leg->set_position(190,90);
}
void init_legs(){
  rb_leg->init_leg_encoder();
  Serial.print("1 ");
  lb_leg->init_leg_encoder();
  Serial.print("2 ");
  lf_leg->init_leg_encoder();
  Serial.print("3 ");
  rf_leg->init_leg_encoder();
  Serial.println("4 ");
  home();
  legs_initialized = 1;
}
//loads a trajectory into the current context.
//The trajectory will begin executing as soon as it can
//will not stop until commanded or out of frames.
int load_trajectory(Trajectory* load_traj)
{
  rf_leg->power(1);
  lf_leg->power(1);
  rb_leg->power(1);
  lb_leg->power(1);
  current_trajectory = load_traj;
  traj_time = 0;
  traj_loaded = 1;

  return traj_time;
}

#if due
void startTimer(uint32_t period)
{
  Timer1.attachInterrupt(timerIsr).start(period);
}
#else

void startTimer()
{
  cli();//stop interrupts
  //set timer1 interrupt at 1kHz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set timer count for 1khz increments
  OCR1A = 19999;// = (16*10^6) / (1000*8) - 1
  //had to use 16 bit timer1 for this bc 1999>255, but could switch to timers 0 or 2 with larger prescaler
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS11 bit for 8 prescaler
  TCCR1B |= (1 << CS11);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei();//allow interrupts

}
#endif
// the setup function runs once when you press reset or power the board
void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(115200);
  sample_period = 10000;

  //the current_execution frame, with heap allocated memory (local_positions)
  curr_frame = new Frame((int*) malloc(sizeof(int)*8));
  simple = new Trajectory(gait_1_size, gait_1); //creates a traj with len 321, and location gait_1
  trot = new Trajectory(gait_2_size, gait_2); //creates a traj with len 321, and location gait_1
  servo_test = new Trajectory(gait_3_size, gait_3); //creates a traj with len 321, and location gait_1
  single_step = new Trajectory(gait_4_size, gait_4); //creates a traj with len 321, and location gait_1
  biped = new Trajectory(gait_5_size, gait_5); //creates a traj with len 321, and location gait_1


  // Initialize the legs

  //dont change the order of instantiation otherwise the encoders will me messed up
  //1 -> RB Leg
  //2 ->LB Leg
  //3 -> RF Leg
  //4 -> LF Leg
  //LOOKING FROM THE BOTTOM OF THE ROBOT
  //notes on the servos
  //looking at the profile, the CCW is 0 the CW is 180
  //front leg 0 appears to be 60 on the front_servo, and 90 on the back.
  //white cable from encoder is SDA
  //yellow cable is clock source
  rb_leg = new Leg(right_back_fwd,right_back_rvs,right_back_servo,right_back_force,0);
  rb_leg->set_sample_freq(sample_period);
  lb_leg = new Leg(left_back_fwd,left_back_rvs,left_back_servo,left_back_force,1);
  lb_leg->set_sample_freq(sample_period);
  lf_leg = new Leg(left_forward_fwd,left_forward_rvs,left_forward_servo,left_forward_force,1);
  lf_leg->set_sample_freq(sample_period);
  rf_leg = new Leg(right_forward_fwd,right_forward_rvs,right_forward_servo,right_forward_force,0);
  rf_leg->set_sample_freq(sample_period);


  delay(50);
  Serial.println("JPG Industries Mutt, Now Online.");
  Timer1.initialize(sample_period); // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
  Timer1.attachInterrupt( timerIsr ); // attach the service routine here

}

void serialEvent() {
  if(Serial.available()>0)
  {
    ByteReceived = Serial.read();
    if(ByteReceived == '1') // Single Quote! This is a character.
    {
      Serial.println("Initializing Legs");
      init_legs();
      Serial.print("Initialization Complete.");
    }
    if(ByteReceived == 'h')
    {
      Serial.print("Pose: Home.");
      home();
    }
    if(ByteReceived == 's')
    {
      Serial.println("Pose: Stand.");
      stand();
    }
    if(ByteReceived == 'g')
    {
      Serial.println("Now loading: Trajectory 4.");
      load_trajectory(single_step);
    }
    if(ByteReceived == 't')
    {
      Serial.println("Now loading: Trajectory 2.");
      load_trajectory(trot);
    }
    if(ByteReceived == 'b')
    {
      Serial.println("Now loading: Trajectory 5.");
      load_trajectory(biped);
    }
    if(ByteReceived == 'q')
    {
      Serial.println("Abort Trajectory.");
      traj_loaded = 0;
    }
    Serial.println();    // End the line
  }
}

// the loop function runs over and over again forever
void loop() {
  if(legs_initialized){
    if(print){
      lb_leg->update_position();
      lf_leg->update_position();
      rb_leg->update_position();
      rf_leg->update_position();
      rf_leg->drive();
      lf_leg->drive();
      rb_leg->drive();
      lb_leg->drive();
      print = 0;

    }


    //if we are in the middle of executing a trajectory and it is time to send
    //a new frame, execute the following
    if(traj_loaded && (curr_time >= traj_period))
    {
      curr_time=0;
      traj_time++;
      //store the frame to execute now into curr_frame
      current_trajectory->get_frame(traj_time,curr_frame);
      curr_frame->print_local();
      //if we're at the end of a traj, reset
      if(curr_frame->is_null())
      {
        current_trajectory = NULL;
        traj_loaded = 0;
        Serial.println("\n\nTrajectory Complete.");
        home();
      }else{
				rf_leg->set_position(curr_frame->local_positions[0],curr_frame->local_positions[1]);
			  lf_leg->set_position(curr_frame->local_positions[2],curr_frame->local_positions[3]);
        rb_leg->set_position(curr_frame->local_positions[4],curr_frame->local_positions[5]);
        lb_leg->set_position(curr_frame->local_positions[6],curr_frame->local_positions[7]);

      }
    }
  }
}
