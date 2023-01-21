#include <msp430x14x.h>

void initPortsLcd(void){
  P2SEL = 0;
  P2OUT = 0;
  P2DIR = ~BIT0;                      
}