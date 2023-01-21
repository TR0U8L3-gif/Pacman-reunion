#include <msp430x14x.h>
#include "lcd/lcd.h"
#include "lcd/portyLcd.h"
#include "game_engine/engine.h"
#include "input/input.h"

char app_initialized = 0;

void main(void)
{
  unsigned char i;
  WDTCTL = WDTPW + WDTHOLD;              
  P2DIR |= BIT1;                        
  BCSCTL1 |= XTS + DIVA1 + DIVA0;         
  do 
  {
    IFG1 &= ~OFIFG;                     
    for (i = 255; i > 0; i--);           
  }
  while ((IFG1 & OFIFG));                      
 
  WDTCTL = WDTPW + WDTCNTCL + WDTTMSEL + WDTSSEL;
  IE1 |= WDTIE;                       
  _EINT();
  
  initLcd();
  initPortsLcd();
  initButtons();
  initSpecial();
  clearDisplay();
  sendString("     PACMAN     ", 0, 0);
  sendString("   REUNION ", 1, 0);
  sendChar(3);
  delayx1s(5);
  app_initialized = 1;
  while(1);
}


#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
  if (app_initialized) app();
}
