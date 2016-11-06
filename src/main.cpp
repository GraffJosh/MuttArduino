/*

*/

#define due 1

#include <Arduino.h>
#include "../lib/motor_control.h"
#if due == 0
//#include <TimerOne.h>
#endif
Leg *lb_leg;
int print = 1, drive = 0;
int sample_freq;
//TC1 ch 0
void TC3_Handler()
{
      #if due
        TC_GetStatus(TC1, 0);
      #endif
				lb_leg->update_position();
				print = 1;
        if(drive < 255)
        {
          drive++;
        }else{
          drive = -255;
        }
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
#endif
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
	Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(115200);
  sample_freq = 10;
  // Initialize the legs
		lb_leg = new Leg();
    lb_leg->set_sample_freq(sample_freq);

    #if due
		startTimer(TC1, 0, TC3_IRQn, sample_freq);
    #else
    Timer1.initialize(100000); // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
    Timer1.attachInterrupt( TC3_Handler ); // attach the service routine here
    #endif
}

// the loop function runs over and over again forever
void loop() {
	//lb_leg->drive();

	if(print)
	{
		print = 0;
    lb_leg->set_position(90);
    lb_leg->drive(lb_leg->get_cmd());

    Serial.print("Drive:");
    Serial.print(lb_leg->get_cmd());
    Serial.print("  pos:");
		Serial.println(lb_leg->get_positon());
  }


}
