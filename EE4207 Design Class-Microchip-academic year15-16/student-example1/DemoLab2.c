 /***********************************************************************
 *	Code Description
 *  
 *  This code demonstrates PWM generation at 1kHz, 50% duty cycle
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
	putsXLCD("Demo 2");

	while(1)
	{
		SetPWM(10000,0.5); //PWM with 10KHz of frequency and 50% of duty cycle
  	}			// end while(1)
}				// end main
