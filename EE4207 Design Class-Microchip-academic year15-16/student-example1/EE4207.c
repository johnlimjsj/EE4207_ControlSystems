#include <p30F6010a.h>
#include "xlcd.h"
#include "EE4207.h"

 /************************Configuration Bits***************************/
// Setting configuration fuses using macros
// Refer to p30F6010a for complete list of settings

// Clock switching, clock monitor disabled.
// XT w/ PLL 4x clock option should be selected.
_FOSC(CSW_FSCM_OFF & XT_PLL4); 
// Watchdog Timer off
_FWDT(WDT_OFF);
// Brown-out and Power On Reset Off and MCLR enabled
_FBORPOR(PBOR_OFF & MCLR_EN);
// Code Protection Off
_FGS(CODE_PROT_OFF);


void Setup(void)
{   
	// Initialize PORTs	
	PORTA = 0;				
	PORTB = 0;				
	PORTC = 0;
	PORTD = 0;
	PORTE = 0;
	PORTG = 0;
	TRISA = 0x39FF;
	TRISB = 0xFFFF;
	TRISC = 0xFFF5;			// RC1 is LCD R/W line
							// RC3 is LCD RS line
							
	TRISD = 0xD7C0;			// RD13 is LCD enable line
							// RD11 is output for PWM_OUTPUT_ENABLE line
							// RD5 is PFC_FIRE line
							// RD4 is BRAKE_FIRE line
							// RD3:RD0 are LCD data lines
	TRISE = 0xFDFF;			// RE9 is output for FAULT_RESET line
	TRISG = 0xFFFD;         // set RG1 as output
	
	//Simple PWM mode
	
	OC8CON = 0x0000; // Turn off output compare module
	PR3 = 0x1CD3;    // Set PWM Period to 1ms
    OC8RS = 0x0E6A; // Set Duty Cycle to 50%
	OC8R = OC8RS;   // 0x0E6A; // Set Initial Duty Cycle to 50%
	OC8CON =0x000E; // TMR3, PWM mode with fault pin disabled
	T3CON = 0x8000; // Start Timer3 


	// Initialize ADC
	
	ADCON1 = 0;
	ADCON2 = 0;
	ADCON3 = 0;
	ADPCFG = 0x0003;
	ADCHS = 0x0007;
	ADCON1bits.ADON = 1;

}

//---------------------------------------------------------------------
// This is a generic delay routine 

void Delay(unsigned int count)
{
unsigned int j;
for(j=0;j<count;j++);
}


//---------------------------------------------------------------------
// ADC function
int ReadADC(unsigned int channel)
{
	int Delay;
	
	if(channel > 0x000F) return(0);
	ADCHS = channel;
	ADCON1bits.SAMP = 1;
	for(Delay = 0; Delay < 20; Delay++);
	IFS0bits.ADIF = 0;
	ADCON1bits.SAMP = 0;
	while(!IFS0bits.ADIF);
	return(ADCBUF0);

}

int SetPWM(int freq, float dutycycle)
{
	//Simple PWM mode
	
    int PR3_count = 7372800/freq-1;
    // PR3 = 0x02E1 for 10kHz, Ox1CD0 for 1kHz
    int OC8RS_count = dutycycle*(PR3_count + 1);
    // int OC8RS_count = dutycycle;

	PR3 = PR3_count; // 0x02E1; // Set PWM Period to 1ms
	OC8RS = OC8RS_count; //0x0E6A; // Set Duty Cycle to 50%

    return(1);
}
