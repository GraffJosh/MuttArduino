/*

*/

#define due 0
#include <Wire.h>
#include <Arduino.h>
#include "../lib/motor_control.h"
#include "../lib/Trajectory.h"
#include <avr/interrupt.h>
#if due == 0
#include <TimerOne.h>
#endif
Leg *lb_leg;
int print = 1, drive = 0, pos_pot=A1;
int sample_freq;
//TC1 ch 0
//ISR(TIMER1_COMPA_vect)
void timerIsr()
{
      #if due
        TC_GetStatus(TC1, 0);
      #endif

      print = 1;
}

#if due
void startTimer(Tc *tc, uint32_t channel, IRQn_Type irq, uint32_t frequency) {
        pmc_set_writeprotect(false);
        pmc_enable_periph_clk((uint32_t)irq);
        TC_Configure(tc, channel, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK4);
        uint32_t rc = VARIANT_MCK/128/frequency; //128 because we selected TIMER_CLOCK4 above
        TC_SetRA(tc, channel, rc/2); //50% high, 50% low
        TC_SetRC(tc, channel, rc);
        TC_Start(tc, channel);
        tc->TC_CHANNEL[channel].TC_IER=TC_IER_CPCS;
        tc->TC_CHANNEL[channel].TC_IDR=~TC_IER_CPCS;
        NVIC_EnableIRQ(irq);
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
  // initialize digital pin LED_BUILTIN as an output.
	Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(115200);
  sample_freq = 10;
  pinMode(pos_pot, INPUT);
  // Initialize the legs
		lb_leg = new Leg();
    lb_leg->set_sample_freq(sample_freq);

    #if due
		startTimer(TC1, 0, TC3_IRQn, sample_freq);
    #else
    Serial.print("setup");
    Timer1.initialize(sample_freq*1000); // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
    Timer1.attachInterrupt( timerIsr ); // attach the service routine here
    //sei();
    // startTimer();
    #endif


    lb_leg->set_position(90);
}

// the loop function runs over and over again forever
void loop() {
	//lb_leg->drive();

	if(print)
	{
		print = 0;
    lb_leg->set_position(map(analogRead(pos_pot), 0,1024,0,180));
    lb_leg->update_position();
    lb_leg->update_force();
    lb_leg->drive(lb_leg->get_position_cmd());


    Serial.print(" Drive:");
    Serial.print(lb_leg->get_position_cmd());
    Serial.print(" Force:");
    Serial.print(lb_leg->get_force());
    Serial.print("  pos:");
		Serial.println(lb_leg->get_position());
  }


}
