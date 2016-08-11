
/*********** Function Definitions *****************************/
void Setup(void);		// Initializes dsPIC and peripherals
void Delay(unsigned int count);
int ReadADC(unsigned int channel);
int SetPWM(int freq, float dutycycle);

// These are the LEDs
#define DIR_LED LATDbits.LATD7		//D5 on PCB
#define LED1 LATAbits.LATA9			//D6 on PCB
#define LED2 LATAbits.LATA10			//D7 on PCB
#define LED3 LATAbits.LATA14			//D8 on PCB
#define LED4 LATAbits.LATA15			//D9 on PCB