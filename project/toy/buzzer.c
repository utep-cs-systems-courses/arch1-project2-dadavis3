#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

static int counter1 = 0; 
static int counter2 = 0; 
static int counter3 = 0;
static int counter4 = 0;

void buzzer_init(){
  /*
    Direct timer A output "TA0.1" to P2.6.
    According to table 21 from data sheet:
    P2SEL2.6, P2SEL2.7, and P2SEL.7 must be zero
    P2SEL.6 must be 1
    Also: P2.6 direction must be output
  */
  timerAUpmode(); /*used to drive speaker*/
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR = BIT6; /*enable output to speaker (P2.6)*/
}

void buzzer_set_period(short cycles){
  CCR0 = cycles;
  CCR1 = cycles >> 1; 
}

void song_1(){
  switch(counter1){
    case 0: buzzer_set_period(450); counter1++; break; 
    case 1:
    case 2: buzzer_set_period(800); counter1++; break; 
    case 3:
    case 4:  
    case 5: buzzer_set_period(1000); counter1++; break; 
    case 7:
    case 9: buzzer_set_period(650); counter1++; break; 
    case 6: buzzer_set_period(800); counter1++; break; 
    case 8:
    case 10: buzzer_set_period(200); counter1++; break;
    case 11:
    case 12: buzzer_set_period(250); if(counter1 == 12){counter1 = 0;} else{counter1++;}; break; 
    }
}

void song_2(){
  switch(counter2){
    case 0: buzzer_set_period(550); counter2++; break; 
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10: buzzer_set_period(80); counter2++; break;
    case 11: buzzer_set_period(200); counter2++; break; 
    case 12:
    case 13: buzzer_set_period(350); counter2++; break;
    case 14: buzzer_set_period(300); counter2++; break; 
    case 15: buzzer_set_period(450); if(counter2 == 15){counter2 = 0;} else{counter2++;}; break;
  }
}

void song_3(){
  switch(counter3){
  case 0: buzzer_set_period(500); counter3++; break;
  case 1: buzzer_set_period(200); counter3++; break;
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7: buzzer_set_period(900); counter3++; break;
  case 8: buzzer_set_period(850); counter3++; break; 
  case 9:
  case 10:
  case 11:
  case 12:
  case 13:
  case 14:
  case 15:  
  case 16: buzzer_set_period(1000); if(counter3 == 16){counter3 = 0;} else{counter3++;}; break;
  }
}

void song_4(){ 
  switch(counter4){
  case 0: buzzer_set_period(250); counter4++; break;
  case 1: buzzer_set_period(250); counter4++; break;
  case 2: buzzer_set_period(250); counter4++; break;
  case 3: buzzer_set_period(250); counter4++; break;
  case 4: buzzer_set_period(250); counter4++; break;
  case 5:
  case 6: 
  case 7: buzzer_set_period(900); counter4++; break;
  case 8:
  case 9:
  case 10: buzzer_set_period(700); counter4++; break;
  case 11:
  case 12:
  case 13:
  case 15:  
  case 14: buzzer_set_period(700); counter4++; break;
  case 16: buzzer_set_period(800); if(counter4 == 16){counter4 = 0;} else{counter4++;}; break;
  }
}



