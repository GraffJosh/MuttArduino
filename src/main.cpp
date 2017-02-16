

#define due 0
#define timingpin 52
#include <Wire.h>
#include <Arduino.h>
#include "../lib/motor_control.h"
#include "../lib/Leg.h"
#include "../lib/Trajectory.h"
#include <avr/interrupt.h>
//#include "../lib/DueTimer/DueTimer.h"
#include "../lib/Servo/src/Servo.h"
#include <TimerOne.h>
#if due == 0
#endif

//Leg declarations
Leg *lb_leg;
Leg *rb_leg;
Leg *lf_leg;
Leg *rf_leg;
Servo servoMotor;
int ByteReceived;
Trajectory simple;
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
}
// #endif

void init_legs(){

  rb_leg->init_leg_encoder();
  lb_leg->init_leg_encoder();
  lf_leg->init_leg_encoder();
  rf_leg->init_leg_encoder();
  legs_initialized = 1;
}


#if due
// void startTimer(Tc *tc, uint32_t channel, IRQn_Type irq, uint32_t frequency) {
//         pmc_set_writeprotect(false);
//         pmc_enable_periph_clk((uint32_t)irq);
//         TC_Configure(tc, channel, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK4);
//         uint32_t rc = VARIANT_MCK/128/frequency; //128 because we selected TIMER_CLOCK4 above
//         TC_SetRA(tc, channel, rc/2); //50% high, 50% low
//         TC_SetRC(tc, channel, rc);
//         TC_Start(tc, channel);
//         tc->TC_CHANNEL[channel].TC_IER=TC_IER_CPCS;
//         tc->TC_CHANNEL[channel].TC_IDR=~TC_IER_CPCS;
//         NVIC_EnableIRQ(irq);
// }
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
  pinMode(timingpin,OUTPUT);
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(115200);
  Serial.println("Starting");
  sample_period = 10000;

  Serial.print("Hello. Its me in Setup.");
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
  //
  lf_leg = new Leg(left_forward_fwd,left_forward_rvs,left_forward_servo,left_forward_force,1);
  lf_leg->set_sample_freq(sample_period);


  //rf leg 1000 is forwards, 2000 is backwards
  rf_leg = new Leg(right_forward_fwd,right_forward_rvs,right_forward_servo,right_forward_force,0);
  rf_leg->set_sample_freq(sample_period);


  #if due
  // startTimer(TC1, 0, TC3_IRQn, sample_period);
  // startTimer(sample_period);
  #else
  Serial.print("setup");
  Timer1.initialize(sample_period); // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
  Timer1.attachInterrupt( timerIsr ); // attach the service routine here
  //sei();
  // startTimer();
  #endif

  simple = Trajectory();
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
    Serial.println();    // End the line
  }
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(timingpin,0);

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
      // Serial.print("Pos: ");
      // Serial.print(lb_leg->get_position());
      // Serial.print(rb_leg->get_position());
      // Serial.print(rf_leg->get_position());
      // Serial.print(", cmd: ");
      // Serial.print(lb_leg->get_position_cmd());
      // Serial.print(rb_leg->get_position_cmd());
      // Serial.print(rf_leg->get_position_cmd());
      // Serial.print(", desire: ");
      // Serial.print();
      // Serial.println();
      // Serial.print(rf_leg->set_position(160));
      // Serial.println(rb_leg->set_position(160));
      rf_leg->set_position(250);
      // lf_leg->set_position(250);
      // lb_leg->set_position(35);
      // rb_leg->set_position(35);

      lf_leg->set_servo(120);
      rf_leg->set_servo(120);
      rb_leg->set_servo(120);
      lb_leg->set_servo(120);
      curr_time=0;
    }
  }
  digitalWrite(timingpin,1);
}
