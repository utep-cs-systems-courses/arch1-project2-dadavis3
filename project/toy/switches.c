#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "buzzer.h"
#include "libTimer.h"



char switch_state_down, switch_state_changed, tempo; 

static char switch_update_interrupt_sense(){
  char val = P2IN;
  /*update switch interrupt to detect changes from current button*/
  P2IES |= (val & SWITCHES); /*if switch up, sense down*/
  P2IES &= (val | ~SWITCHES); /*if switch down, sense up*/
  return val;
}

void switch_init() /*setup switch*/
{  
  P2REN |= SWITCHES; /*enables resistors for switches*/
  P2IE = SWITCHES; /*enable interrupts from switches*/
  P2OUT |= SWITCHES; /*pull-ups for switches*/
  P2DIR &= ~SWITCHES; /*set switches' bits for input*/
}

void switch_interrupt_handler(){
  char p2val = switch_update_interrupt_sense();
  if(!(p2val & SW1)){ /*Play song_1 while pressing SW1*/
    tempo = 25;
    song_1();
    switch_state_down = 1;
    
  }

  else if(!(p2val & SW2)){ /*Play song_2 while pressing SW2*/
    tempo = 50;
    song_2();
    switch_state_down = 1;
  }

  else if(!(p2val & SW3)){ /*Play song_3 while pressing SW3*/
    tempo = 75;
    song_3();
    switch_state_down = 1;
  }

  else if(!(p2val & SW4)){ /*Play song_4 while pressing SW4*/
    tempo = 100;
    song_4();
    switch_state_down = 1;
  }

  switch_state_changed = 1;
  led_update();
}
