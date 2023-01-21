#ifndef LCD_H
#define LCD_H
void initLcd(void);
void initSpecial(void);
void clearDisplay(void);
void sendCmd (unsigned char e);
void sendChar (unsigned char c);
void sendString(const char* string, unsigned char line, unsigned char offset);
void sendPoints(unsigned short int number, unsigned char line, unsigned char offset);
void sendHealth(char health);
void sendPowerUp(char powerUp);
void delayx1s(unsigned char b);
void delayx100us(unsigned char b);
#endif