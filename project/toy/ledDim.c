#include <msp430.h>
#include "led.h"

unsigned char red_on = 0, green_on = 0, led_changed = 0; // Red on, green on and changing state of LED
static char redVal[] = {0, LED_RED}, greenVal[] = {0, LED_GREEN};

void led_init_dim(){

  P1DIR |= LEDS;
  led_changed = 1;
  led_update();

}

void led_update_dim(){

  if(led_changed){

    char ledFlags = redVal[red_on] | greenVal[green_on];
    P1OUT &= (0xff^LEDS) | ledFlags; // clears bits for off leds
    P1OUT |= ledFlags;
    led_changed = 0;
      
  }

}
