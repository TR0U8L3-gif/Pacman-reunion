#include <msp430x14x.h>
#include "lcd.h"
#include "portyLcd.h"

#define bitset(var,bitno) ((var) |= 1 << (bitno))
#define bitclr(var,bitno) ((var) &= ~(1 << (bitno)))

void delay (unsigned int a){
  int k;
  for (k=0 ; k != a; ++k) {
    _NOP();
    _NOP();
    _NOP();
    _NOP();
  }
}

void delayx1s(unsigned char b){
  int j;
  for (j=0; j!=b; ++j) delay (_1s);
}

void delayx100us(unsigned char b){
  int j;
  for (j=0; j!=b; ++j) delay (_100us);
}

void _E(void){
  bitset(P2OUT,E);		//toggle E for LCD
	delay(_10us);
	bitclr(P2OUT,E);
}

void initLcd(void){
    bitclr(P2OUT,RS);
    delayx100us(250);                   //Delay 100ms
    delayx100us(250);
    delayx100us(250);
    delayx100us(250);
    LCD_Data |= BIT4 | BIT5;            //D7-D4 = 0011
    LCD_Data &= ~BIT6 & ~BIT7;
    _E();                               //toggle E for LCD
    delayx100us(100);                   //10ms
    _E();                               //toggle E for LCD
    delayx100us(100);                   //10ms
    _E();                               //toggle E for LCD
    delayx100us(100);                   //10ms
    LCD_Data &= ~BIT4;
    _E();                               //toggle E for LCD

    sendCmd(DISP_ON);
    sendCmd(CLR_DISP);
    delayx100us(250);
    delayx100us(250);
    delayx100us(250);
    delayx100us(250);
}

void initSpecial(void){
  sendCmd(CG_RAM_ADDR);
  int spec[8][8] = {
     {0,14,31,21,31,31,21,0},//normal ghost
     {0,14,21,27,21,31,21,0},//weak ghost
     {14,31,23,31,31,3,31,14},//normal pacman
     {14,31,23,31,7,3,7,30},//powered up pacman
     {0,0,0,0,4,14,4,0},//point
     {28,20,28,16,21,5,5,7},//power up
     {0,0,10,21,17,10,4,0},//empty hp
     {0,0,10,31,31,14,4,0}//full hp
  };
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      sendChar(spec[i][j]);
    }
  }
}

void clearDisplay(void) {
    sendCmd(CLR_DISP);
    delayx100us(10);
}

void sendCmd(unsigned char e){
  int temp;
	delayx100us(10);                //10ms
	temp = e & 0xf0;		//get upper nibble	
	LCD_Data &= 0x0f;
	LCD_Data |= temp;               //send CMD to LCD
	bitclr(P2OUT,RS);     	        //set LCD to CMD mode
	_E();                           //toggle E for LCD
	temp = e & 0x0f;
	temp = temp << 4;               //get down nibble
	LCD_Data &= 0x0f;
	LCD_Data |= temp;
	bitclr(P2OUT,RS);   	        //set LCD to CMD mode
	_E();                           //toggle E for LCD
}

void sendChar(unsigned char d){
  int temp;
	delayx100us(5);                 //.5ms	
	temp = d & 0xf0;		//get upper nibble	
	LCD_Data &= 0x0f;
	LCD_Data |= temp;
	bitset(P2OUT,RS);     	        //set LCD to data mode
	_E();                           //toggle E for LCD
	temp = d & 0x0f;
	temp = temp << 4;               //get down nibble
	LCD_Data &= 0x0f;
	LCD_Data |= temp;
	bitset(P2OUT,RS);   	        //set LCD to data mode
	_E();                           //toggle E for LCD
}

void sendString(const char* string, unsigned char line, unsigned char offset){
  if (line % 2 == 0) sendCmd(DD_RAM_ADDR + offset);
  else sendCmd(DD_RAM_ADDR2 + offset);
  int i = 0;
  while(string[i] != '\0')
  {
    sendChar(string[i]);
    i++;
  }
}

void sendPoints(unsigned short int number, unsigned char line, unsigned char offset)
{
  char numbers[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  if (line % 2 == 0) sendCmd(DD_RAM_ADDR + offset);
  else sendCmd(DD_RAM_ADDR2 + offset);
  sendChar(numbers[number/1000]);
  sendChar(numbers[(number/100)%10]);
  sendChar(numbers[(number/10)%10]);
  sendChar(numbers[number%10]);
}

void sendHealth(char health){
  sendCmd(DD_RAM_ADDR + 14);
  sendChar(health >= 1 ? 15 : 14);
  sendCmd(DD_RAM_ADDR + 15);
  sendChar(health >= 2 ? 15 : 14);
  sendCmd(DD_RAM_ADDR2 + 14);
  sendChar(health >= 3 ? 15 : 14);
  sendCmd(DD_RAM_ADDR2 + 15);
  sendChar(health >= 4 ? 15 : 14);
}

void sendPowerUp(char powerUp){
  sendString("    ",1,0);
  sendCmd(DD_RAM_ADDR2);
  for (char i = 0; i < powerUp; i++){
    sendChar(5);
  }
}