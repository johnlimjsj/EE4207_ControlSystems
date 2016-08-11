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
 *    Author: Steve Bowling                                            * 
 *                                                                     *
 *    Filename:       xlcd.h					                       *
 *    Date:           11/01/06                                         *
 *    File Version:   2.00                                             *
 *                                                                     *
 *    Tools used:    Compiler  -> 2.03                                 *
 *                                                                     *
 *    Linker File:    p30f6010a.gld                                    *
 *                                                                     *
 *                                                                     *
 ***********************************************************************/

/* $Id: xlcd.h,v 1.2 2000/02/09 22:58:35 ConnerJ Exp $ */
/* Modified by CRE 3/01/03 to allow for dsPIC */
/* NB This version of the LCD routines only supports lower 4 bit*/
#ifndef __XLCD_H
#define __XLCD_H

/*30F6010 XLCD peripheral routines for use on dsPIC30F Motor Control Dev Board.
 *
 *   Notes:
 *      - These libraries routines are written to support the
 *        Hitachi HD44780 LCD controller.
 *      - The user must define the following items:
 *          - The LCD interface type (4- or 8-bits)
 *          - If 4-bit mode
 *              - whether using the upper or lower nibble
 *          - The data port
 *              - The tris register for data port
 *              - The control signal ports and pins
 *              - The control signal port tris and pins
 *          - The user must provide three delay routines:
 *              - DelayFor18TCY() provides a 18 Tcy delay
 *              - DelayPORXLCD() provides at least 15ms delay
 *              - DelayXLCD() provides at least 5ms delay
 */

/* Interface type 8-bit or 4-bit
 * For 4-bit operation uncomment the #define BIT8
 */
// #define BIT8 

/* When in 4-bit interface define if the data is in the upper
 * or lower nibble.  For lower nibble, uncomment the #define UPPER
 */
// #define UPPER

/* DATA_PORT defines the port to which the LCD data lines are connected */
#define DATA_PORT	   PORTD
#define TRIS_DATA_PORT TRISD


/* CTRL_PORT defines the port where the control lines are connected.
 * These are just samples, change to match your application.
 */

#define RW_PIN   PORTCbits.RC1   /* PORT for RW */
#define TRIS_RW  TRISCbits.TRISC1   /* TRIS for RW */
#define RS_PIN   PORTCbits.RC3   /* PORT for RS */
#define TRIS_RS  TRISCbits.TRISC3   /* TRIS for RS */
#define E_PIN    PORTDbits.RD13  /* PORT for E  */
#define TRIS_E   TRISDbits.TRISD13  /* TRIS for E  */


/* Display ON/OFF Control defines */
#define DON         0x0f  /* Display on      */
#define DOFF        0x0b  /* Display off     */
#define CURSOR_ON   0x0f  /* Cursor on       */
#define CURSOR_OFF  0x0d  /* Cursor off      */
#define BLINK_ON    0x0f  /* Cursor Blink    */
#define BLINK_OFF   0x0e  /* Cursor No Blink */

/* Cursor or Display Shift defines */
#define SHIFT_CUR_LEFT    0x13  /* Cursor shifts to the left   */
#define SHIFT_CUR_RIGHT   0x17  /* Cursor shifts to the right  */
#define SHIFT_DISP_LEFT   0x1b  /* Display shifts to the left  */
#define SHIFT_DISP_RIGHT  0x1f  /* Display shifts to the right */

/* Function Set defines */
#define FOUR_BIT   0x2f  /* 4-bit Interface               */
#define EIGHT_BIT  0x3f  /* 8-bit Interface               */
#define LINE_5X7   0x33  /* 5x7 characters, single line   */
#define LINE_5X10  0x37  /* 5x10 characters               */
#define LINES_5X7  0x38  /* 5x7 characters, multiple line */

/* OpenXLCD
 * Configures I/O pins for external LCD
 */

void OpenXLCD(unsigned char);

/* SetCGRamAddr
 * Sets the character generator address
 */
void SetCGRamAddr(unsigned char);

/* SetDDRamAddr
 * Sets the display data address
 */

void SetDDRamAddr(unsigned char);

/* BusyXLCD
 * Returns the busy status of the LCD
 */
unsigned char BusyXLCD(void);

/* ReadAddrXLCD
 * Reads the current address
 */
unsigned char ReadAddrXLCD(void);

/* ReadDataXLCD
 * Reads a byte of data
 */
char ReadDataXLCD(void);

/* WriteCmdXLCD
 * Writes a command to the LCD
 */

void WriteCmdXLCD(unsigned char);


/* WriteDataXLCD
 * Writes a data byte to the LCD
 */

void WriteDataXLCD( unsigned char);

/* putcXLCD
 * A putc is a write
 */
#define putcXLCD WriteDataXLCD

/* putsXLCD
 * Writes a string of characters to the LCD
 */

void putsXLCD(unsigned char *);


/* putrsXLCD
 * Writes a string of characters in ROM to the LCD
 */

void putrsXLCD(const unsigned char *);


/* User defines these routines according to the oscillator frequency */

void DelayFor18TCY(void);
void DelayPORXLCD(void);
void DelayXLCD(void);


#endif
