#include <msp430.h>
#include "switches.h"
#include "buzzer.h"

void
__interrupt_vec(WDT_VECTOR) WDT(){
  static char time_count = 0;
  if(++time_count == tempo){
    int counter = 1;
    while(counter <= 10){
      int count = 0;
      buzzer_set_period(0);
      while(count < 10000){
	count++;
      }
      counter++;
    }
    switch_interrupt_handler();
    time_count = 0;
  }
}
 
