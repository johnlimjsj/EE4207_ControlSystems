/***********************************************************************
 *	Code Description
 *  
 *  This code demonstrates how to measure the running time
 *    of while loop.
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
	putsXLCD("Demo 4");

	while(1)
	{
        LATG= LATG & 0xFFFD;  // Set RG1 = 0
        Delay(50000);
        LATG= LATG | 0x0002; // Set RG1 = 1
        Delay(70000);
  	}			// end while(1)
}				// end main
