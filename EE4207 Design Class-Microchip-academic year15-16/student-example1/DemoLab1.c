/***********************************************************************
 *	Code Description
 *  
 *  This code demonstrates the use of ADC 
 *  and lighting up of LEDs with increasing value
 * 
 **********************************************************************/

#include <libpic30.h>
#include <stdio.h>
#include <p30F6010a.h>
#include "xlcd.h"
#include "EE4207.h"

#define VOLTPERCOUNT 5.0/1023

int main( void )
{
	int adcvalue;
    char  buf[20];

	Setup();

    //LCD display 
	OpenXLCD(FOUR_BIT&LINES_5X7);	
	Delay(50000);	
	while(BusyXLCD());
	SetDDRamAddr(0);
	putsXLCD("EE4207 Lab");	
	while(BusyXLCD());
	SetDDRamAddr(0x40);
	putsXLCD("Demo 1");

	while(1)
	{
		adcvalue = ReadADC(7);

		if (adcvalue <200 && adcvalue >=0)
		{
			LED1 = 0;
			LED2 = 0;
			LED3 = 0;
			LED4 = 0;	
		}

		if (adcvalue <400 && adcvalue >=200)
		{
			LED1 = 1;
			LED2 = 0;
			LED3 = 0;
			LED4 = 0;	
		}

		if (adcvalue <600 && adcvalue >=400)
		{
			LED1 = 1;
			LED2 = 1;
			LED3 = 0;
			LED4 = 0;	
		}

		if (adcvalue <800 && adcvalue >=600)
		{
			LED1 = 1;
			LED2 = 1;
			LED3 = 1;
			LED4 = 0;	
		}

		if (adcvalue >800)
		{
			LED1 = 1;
			LED2 = 1;
			LED3 = 1;
			LED4 = 1;		
		}

         sprintf(buf, "%d ", adcvalue);
         SetDDRamAddr(0x47);
         putsXLCD("ADC=");
         SetDDRamAddr(0x4B);
         putsXLCD(buf);
  	}			// end while(1)
}				// end main
