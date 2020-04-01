#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

void buzzer_init()
{
    /* 
       Direct timer A output "TA0.1" to P2.6.  
        According to table 21 from data sheet:
          P2SEL2.6, P2SEL2.7, anmd P2SEL.7 must be zero
          P2SEL.6 must be 1
        Also: P2.6 direction must be output
    */
    timerAUpmode();		/* used to drive speaker */
    P2SEL2 &= ~(BIT6 | BIT7);
    P2SEL &= ~BIT7; 
    P2SEL |= BIT6;
    P2DIR = BIT6; /* enable output to speaker (P2.6) */
    
}

void buzzer_set_period(short cycles) /* buzzer clock = 2MHz.  (period of 1k results in 2kHz tone) */
{
  CCR0 = cycles; 
  CCR1 = cycles >> 1;		/* one half cycle */
}

void stop_buzzer(){
  buzzer_set_period(0);
}

void play_song(){
  int song[] = {3135.96,3729.31,4186.01,3135.96,3729.31,4434.92,4186.01,3135.96,3729.31,4186.01,3729.31,3135.96,3135.96};
  static int c= 0;

  buzzer_set_period(song[c]); // setting the period for the song 
  c++;
}

// plays a sequence of sounds
void play_sounds(){
  int song[] = {659,659,698,784,784,698,659,587,523,523,587,659,659,587,587};
  static int c= 0;
  
  buzzer_set_period(song[c]); // setting the period of sequence sounds
  c++;
}
