#ifndef PORTSLCD_H
#define PORTSLCD_H

#define     LCD_Data            P2OUT
#define     _1s                 1000000
#define     _100us              100        
#define     _10us               10             
#define     E                   3            
#define     RS                  2           

#define		CLR_DISP		    0x01
#define		DISP_OFF		    0x08
#define		DISP_ON			    0x0c

#define		DD_RAM_ADDR		    0x80
#define		DD_RAM_ADDR2		0xc0
#define		CG_RAM_ADDR		    0x40

void initPortsLcd(void);

#endif