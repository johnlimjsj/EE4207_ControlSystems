/**********************************************************************
 *                                                                     *
 *                        Software License Agreement                   *
 *                                                                     *
 *    The software supplied herewith by Microchip Technology           *
 *    Incorporated (the "Company") for its dsPIC controller            *
 *    is intended and supplied to you, the Company's customer,         *
 *    for use solely and exclusively on Microchip dsPIC                *
 *    products. The software is owned by the Company and/or its        *
 *    supplier, and is protected under applicable copyright laws. All  *
 *    rights are reserved. Any use in violation of the foregoing       *
 *    restrictions may subject the user to criminal sanctions under    *
 *    applicable laws, as well as to civil liability for the breach of *
 *    the terms and conditions of this license.                        *
 *                                                                     *
 *    THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION.  NO           *
 *    WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING,    *
 *    BUT NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND    *
 *    FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE     *
 *    COMPANY SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL,  *
 *    INCIDENTAL OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.  *
 *                                                                     *
  **********************************************************************/

 /**********************************************************************
 *                                                                     * 
 *    Author: Smart Power Soutions, LLP                                * 
 *                                                                     *
 *    Filename:lcd_drivers.c          	                               *
 *    Date:           11/01/06                                         *
 *    File Version:   5.10                                             *
 *    Project:        53                                               *
 *    Drawing:        2                                                *
 *                                                                     *
 *    Tools used:    MPLAB C30 Compiler v 2.03                         *
 *                                                                     *
 *    Linker File:    p30f6010a.gld                                    *
 *                                                                     *
 *                                                                     *
 ***********************************************************************
 *	Code Description
 *  
 *  These are the low level drivers for the character LCD display.
 *  These routines were taken from the Microchip C18 compiler library
 *  and modified for use on the dsPIC.  In particular, these routines
 *  will only work using a 4-bit interface to the LCD.  The 4 data 
 *  lines must be connected to the lower nibble of a dsPIC port.
 *
 *  Note:  These routines contain delay routines which must be modified
 *  based on the device clock frequency.  As written, these routines
 *  work for a device instruction cycle frequency of 7.38 MHz.
 * 
 **********************************************************************/

#include <p30f6010a.h>
#include "xlcd.h"

void Wait(unsigned int count);
#define BUSY_DELAY	400

/********************************************************************
*       Function Name:  BusyXLCD                                    *
*       Return Value:   char: busy status of LCD controller         *
*       Parameters:     void                                        *
*       Description:    This routine reads the busy status of the   *
*                       Hitachi HD44780 LCD controller.             *
********************************************************************/
unsigned char BusyXLCD(void)
{
	return 0;
}


/********************************************************************
*       Function Name:  OpenXLCD                                     *
*       Return Value:   void                                         *
*       Parameters:     lcdtype: sets the type of LCD (lines)        *
*       Description:    This routine configures the LCD. Based on    *
*                       the Hitachi HD44780 LCD controller. The      *
*                       routine will configure the I/O pins of the   *
*                       microcontroller, setup the LCD for 4-bit     *
*                       mode and clear the display. The user  	     *
*                       must provide three delay routines:           *
*                       DelayFor18TCY() provides a 18 Tcy delay      *
*                       DelayPORXLCD() provides at least 15ms delay  *
*                       DelayXLCD() provides at least 5ms delay      *
**********************************************************************/
void OpenXLCD(unsigned char lcdtype)
{

   Wait(0xFFFF);
   Wait(0xFFFF);
   Wait(0xFFFF);
   Wait(0xFFFF);	

    // write ms nibble to port
    LATD = (LATD & 0xFFF0) | (3); 

    // make PORTD output 
    TRISD = TRISD & 0xFFF0;

    // clear R/!W for write
    RW_PIN = 0;
    
    // toggle enable for > 1 usec
    E_PIN = 1;
    Wait(20);
    E_PIN = 0;

    Wait(0xFFFF);
    
   
    // write ls nibble to port
    LATD = (LATD & 0xFFF0) | (3);
    
    
    // toggle enable for > 1 usec
    E_PIN = 1;
    Wait(20);
    E_PIN = 0;

    // write ms nibble to port
    LATD = (LATD & 0xFFF0) | (3); 

    // make PORTD output 
    TRISD = TRISD & 0xFFF0;

    // clear R/!W for write
    RW_PIN = 0;
    
    // *** Added for LCD timing
    Wait(5);

    // toggle enable for > 1 usec
    E_PIN = 1;
    Wait(20);
    E_PIN = 0;

    Wait(400);

    // write ls nibble to port
    LATD = (LATD & 0xFFF0) | (2); 
    
    // toggle enable for > 1 usec
    E_PIN = 1;
    Wait(20);
    E_PIN = 0;

                    
    WriteCmdXLCD(0x28);   // Function set: 4 bit data, L1652                               
    WriteCmdXLCD(0x06);   // Entry Mode: Inc 1, no shift
    WriteCmdXLCD(0x0C);   // Display ON, Cursor off, no blink
    WriteCmdXLCD(0x01);   // Clear Display
    WriteCmdXLCD(0x80);   // Set Cursor to top left

        return;
}

/********************************************************************
*       Function Name:  putsXLCD
*       Return Value:   void
*       Parameters:     buffer: pointer to string
*       Description:    This routine writes a string of bytes to the
*                       Hitachi HD44780 LCD controller. The user
*                       must check to see if the LCD controller is
*                       busy before calling this routine. The data
*                       is written to the character generator RAM or
*                       the display data RAM depending on what the
*                       previous SetxxRamAddr routine was called.
********************************************************************/
void putsXLCD(unsigned char *buffer)
{
        while(*buffer)                  // Write data to LCD up to null
        {
                WriteDataXLCD(*buffer); // Write character to LCD
                buffer++;               // Increment buffer
        }
        return;
}

/********************************************************************
*       Function Name:  SetDDRamAddr                                *
*       Return Value:   void                                        *
*       Parameters:     CGaddr: display data address                *
*       Description:    This routine sets the display data address  *
*                       of the Hitachi HD44780 LCD controller. The  *
*                       user must check to see if the LCD controller*
*                       is busy before calling this routine.        *
********************************************************************/
void SetDDRamAddr(unsigned char bValue)
{
    unsigned char bTemp;
    bTemp = bValue | 0x80;

	// Wait 1milsec for not busy
	Wait(BUSY_DELAY);  

	// clear RS for Instruction
	RS_PIN = 0;

    // write ms nibble to port
    LATD = (LATD & 0xFFF0) | (bTemp >> 4 & 0x000F); 

    // make PORTD output 
    TRISD = TRISD & 0xFFF0;

    // clear R/!W for write
    RW_PIN = 0;
    
    // toggle enable for > 1 usec
    E_PIN = 1;
    Wait(20);
    E_PIN = 0;

    Wait(20);

    // write ls nibble to port
    LATD = (LATD & 0xFFF0) | (bValue & 0x000F); 

    // clear R/!W for write
    RW_PIN = 0;
    
    
    // toggle enable for > 1 usec
    E_PIN = 1;
    Wait(20);
    E_PIN = 0;

    //make PORTD input;
    TRISD =  TRISD | 0x000F;

    return;
}
/********************************************************************
*       Function Name:  WriteCmdXLCD                                *
*       Return Value:   void                                        *
*       Parameters:     cmd: command to send to LCD                 *
*       Description:    This routine writes a command to the Hitachi*
*                       HD44780 LCD controller. The user must check *
*                       to see if the LCD controller is busy before *
*                       calling this routine.                       *
********************************************************************/
void WriteCmdXLCD(unsigned char bValue)
{
    unsigned char bTemp;
    bTemp = bValue;

	// Wait 1milsec for not busy

	Wait(BUSY_DELAY);

	// clear RS for Instruction
	RS_PIN = 0;

    // write ms nibble to port
    LATD = (LATD & 0xFFF0) | (bTemp >> 4 & 0x000F); 

    // make PORTD output 
    TRISD = TRISD & 0xFFF0;

    // clear R/!W for write
    RW_PIN = 0;
    
    // toggle enable for > 1 usec
    E_PIN = 1;
    Wait(20);
    E_PIN = 0;

    Wait(20);

    // write ls nibble to port
    LATD = (LATD & 0xFFF0) | (bValue & 0x000F); 

    // clear R/!W for write
    RW_PIN = 0;
    
    
    // toggle enable for > 1 usec
    E_PIN = 1;
    Wait(20);
    E_PIN = 0;

    //make PORTD input;
    TRISD =  TRISD | 0x000F;

    return;
}

/********************************************************************
*       Function Name:  WriteDataXLCD                               *
*       Return Value:   void                                        *
*       Parameters:     data: data byte to be written to LCD        *
*       Description:    This routine writes a data byte to the      *
*                       Hitachi HD44780 LCD controller. The user    *
*                       must check to see if the LCD controller is  *
*                       busy before calling this routine. The data  *
*                       is written to the character generator RAM or*
*                       the display data RAM depending on what the  *
*                       previous SetxxRamAddr routine was called.   *
********************************************************************/
void WriteDataXLCD(unsigned char bValue)
{

    unsigned char bTemp;
    bTemp = bValue;

	// Wait 1milsec for not busy
	Wait(BUSY_DELAY);  

	// clear RS for Instruction
	RS_PIN = 1;

    // write ms nibble to port
    LATD = (LATD & 0xFFF0) | (bTemp >> 4 & 0x000F); 

    // make PORTD output 
    TRISD = TRISD & 0xFFF0;

    // clear R/!W for write
    RW_PIN = 0;
    
    // toggle enable for > 1 usec
    E_PIN = 1;
    Wait(20);
    E_PIN = 0;

    Wait(20);

    // write ls nibble to port
    LATD = (LATD & 0xFFF0) | (bValue & 0x000F); 

    // clear R/!W for write
    RW_PIN = 0;
    
    
    // toggle enable for > 1 usec
    E_PIN = 1;
    Wait(20);
    E_PIN = 0;

    //make PORTD input;
    TRISD =  TRISD | 0x000F;

    return;

}

void Wait(unsigned int count)
{
         while(count--);
}




