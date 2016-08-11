/***********************************************************************
 *	Code Description
 *  
 *  This code demonstrates the use of ADC 
 *  to vary PWM duty cycle
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
	Setup();

    //LCD display 
	OpenXLCD(FOUR_BIT&LINES_5X7);	
	Delay(50000);	
	while(BusyXLCD());
	SetDDRamAddr(0);
	putsXLCD("EE4207 Lab");	
	while(BusyXLCD());
	SetDDRamAddr(0x40);
	putsXLCD("Demo 3");

    int adcvalue;

	while(1)
	{
        adcvalue=ReadADC(7);
        SetPWM(10000,adcvalue/1023.0); 
  	}			// end while(1)
}				// end main
