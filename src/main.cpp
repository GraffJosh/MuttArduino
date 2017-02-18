

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
#include <TimerOne.h>
#if due == 0
#endif

int traj_time = 0,traj_period=25,traj_loaded=0;
Trajectory* current_trajectory;
Trajectory* simple;//(100, walk_1);
Frame* curr_frame;

//Leg declarations
Leg *lb_leg;
Leg *rb_leg;
Leg *lf_leg;
Leg *rf_leg;
Servo servoMotor;
int ByteReceived;
int print = 1, drive = 0,upper_pos_pot=A0, lower_pos_pot=A1;
int servo_pos = 0;
int sample_period;
int legs_initialized = 0;
volatile unsigned int curr_time = 0;
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
    ++traj_time;
  }
}
// #endif

void init_legs(){
  rb_leg->init_leg_encoder();
  lb_leg->init_leg_encoder();
  lf_leg->init_leg_encoder();
  rf_leg->init_leg_encoder();


  legs_initialized = 1;
}

//loads a trajectory into the current context.
//The trajectory will begin executing as soon as it can
//will not stop until commanded or out of frames.
int load_trajectory(Trajectory* load_traj)
{
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
  curr_frame =new Frame((int*)malloc(sizeof(int)*8));
  simple = new Trajectory(321, gait_1); //creates a traj with len 321, and location gait_1


  // Initialize the legs

  //dont change the order of instantiation otherwise the encoders will me messed up
  //1 -> RB Leg
  //2 ->LB Leg
  //3 -> RF Leg
  //4 -> LF Leg
  //LOOKING FROM THE BOTTOM OF THE ROBOT

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
      Serial.print("Initializing Legs");
      init_legs();
    }
    if(ByteReceived == '0')
    {
      Serial.print("RECEIVED 0");
    }
    if(ByteReceived == 'g')
    {
      Serial.println("Now loading: Trajectory 1.");
      load_trajectory(simple);
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
      ++curr_time;

    }
    if(curr_time == 10)
    {

      curr_time=0;
    }
    if(traj_loaded && (traj_time % traj_period)==0)
    {
      current_trajectory->get_frame(traj_time,curr_frame);
      Serial.print("Exec Frame");
      curr_frame->print();


      if(curr_frame->is_null())
      {
        current_trajectory = NULL;
        traj_loaded = 0;
      }else{

        rb_leg->set_position(curr_frame->local_positions[4],curr_frame->local_positions[5]);
        lb_leg->set_position(curr_frame->local_positions[2],curr_frame->local_positions[3]);
        rf_leg->set_position(curr_frame->local_positions[0],curr_frame->local_positions[1]);
        lf_leg->set_position(curr_frame->local_positions[6],curr_frame->local_positions[7]);
        Serial.print(lf_leg->get_position_cmd());
      }
    }
  }
}
