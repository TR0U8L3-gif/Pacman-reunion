#include <msp430x14x.h>

void initButtons(void){
  P4DIR &= 0xf0;
}

char buttonDown(char number){
  switch(number)
  {
    case 1: return ~P4IN & BIT4;
    case 2: return ~P4IN & BIT5;
    case 3: return ~P4IN & BIT6;
    case 4: return ~P4IN & BIT7;
    default: return 0;
  }
}

char buttonUp(char number){
  return !buttonDown(number);
}

char anyButtonDown(){
  return buttonDown(1) || buttonDown(2) || buttonDown(3) || buttonDown(4);
}