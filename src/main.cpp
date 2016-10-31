/*

*/
#include <Arduino.h>
#include "../lib/motor_control.h"
Leg *lb_leg;
int print = 0;
int sample_freq;
//TC1 ch 0
void TC3_Handler()
{
        TC_GetStatus(TC1, 0);
        lb_leg->update_position();
        print += 1;
}

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

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
	Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(115200);
  sample_freq = 5;
  // Initialize the legs
		lb_leg = new Leg();
    lb_leg->set_sample_freq(sample_freq);
		startTimer(TC1, 0, TC3_IRQn, sample_freq);
}

// the loop function runs over and over again forever
void loop() {
  if(print == 5)
  {
      Serial.print("curr_pos: ");
      Serial.println(lb_leg->get_position());
      lb_leg->set_position(-60);
      print = 0;
  }

}
