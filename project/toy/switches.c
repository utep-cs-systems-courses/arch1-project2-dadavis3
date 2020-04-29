#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "buzzer.h"

char switch_state_down, switch_state_changed, speed; /* effectively boolean */

static char 
switch_update_interrupt_sense()
{
  char p1val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p1val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p1val | ~SWITCHES);	/* if switch down, sense up */
  return p1val;
}

void switch_init()			/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE = SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
  switch_interrupt_handler();
  led_update();
}

void switch_interrupt_handler()
{
  char p1val = switch_update_interrupt_sense();

  char button1 = (p1val & SW1) ? 0 : 1;
  char button2 = (p1val & SW2) ? 0 : 1;
  char button3 = (p1val & SW3) ? 0 : 1;
  char button4 = (p1val & SW4) ? 0 : 1;

   
  if(button1){
    // switch_state_down = button1;
    buzzer_init();
    play_sounds();
  }
  if(button2){
    switch_state_down = button2;    /* 0 when SW2 is up */
    switch_state_changed = 1;
    led_update();
  }
  if(button3){
    switch_state_down = button3; /* 0 when SW3 is up */
    buzzer_init();
    stop_buzzer();
  }
  if(button4){
    //configureClocks(); /* setup master oscillator, CPU & peripheral clocks */
    led_init_dim();
    speed+=20;
   _enable_interrupts(); /* enable periodic interrupt */
  }
}
