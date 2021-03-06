#include <msp430.h>
#include "led.h"
#include "switches.h"
#include "buzzer.h"


//unsigned char red_on = 0;
//unsigned char green_on = 0;
//unsigned char led_changed = 0;

//static char redVal[] = {0, LED_RED};
//static char greenVal[] = {0, LED_GREEN};

void led_init()
{
  P1DIR |= LEDS;		// bits attached to leds are output
  switch_state_changed = 1;
  led_update();
}

void led_update(){
  if(switch_state_changed){
    char ledFlags = 0; // no LEDs on
    
    ledFlags |= switch_state_down ? LED_GREEN : 0;
    ledFlags |= switch_state_down ? 0 : LED_RED;

    P1OUT &= (0xff - LEDS) | ledFlags;  // clear bits for off leds
    P1OUT |= ledFlags;
  }
  switch_state_changed = 0;
}
