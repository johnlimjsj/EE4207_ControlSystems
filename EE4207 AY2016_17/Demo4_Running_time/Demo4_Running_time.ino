int freq;
int value_temp;

void setup() {
  // put your setup code here, to run once:
    // Turn off the timer while we make changes
  TCCR1B = TCCR1B & ~ ((1 << CS12) | (1 << CS11) | (1 << CS10));
  
  // Ensure the Timer 1 output pins are configured for output
  pinMode( 9, OUTPUT );   //Configures the Pin 9 to behave either as an output
  pinMode( 10, OUTPUT ); //Configures the Pin 10 to behave either as an output
  
  // Set Compare Output Mode and part of the Waveform Generation Mode (mode 14)
  TCCR1A = 
      (1 << COM1A1) | (0 << COM1A0)  // Clear OC1A on Compare Match, set OC1A at BOTTOM (non-inverting mode)
      |
      (1 << COM1B1) | (1 << COM1B0)  // Set OC1B on Compare Match, clear OC1B at BOTTOM (inverting mode)
      |
      (1 << WGM11) | (0 << WGM10);  // Mode 14: Fast PWM, TOP = ICR1, Update of OCR1x at BOTTOM, TOV1 Flag Set on TOP

  // Set the other half of the Waveform Generation Mode (mode 14) and ensure a few things are disabled
  TCCR1B =
      (0 << ICNC1)  // Input Capture Noise Canceler disabled
      |
      (0 << ICES1)  // Input Capture Edge Select don't care
      |
      (1 << WGM13) | (1 << WGM12)  // Mode 14: Fast PWM, TOP = ICR1, Update of OCR1x at BOTTOM, TOV1 Flag Set on TOP
      |
      (0 << CS12) | (0 << CS11) | (0 << CS10);  // Clock continues to be disabled.  Not yet finished configuring.

  // Set the output frequency
  // fOCnxPWM = fclk_I/O / (N * (1 + TOP))
  // fOCnxPWM = 16000000 / (8 * (1 + 199))
  // fOCnxPWM = 10000 Hz
  freq=10000; // set frequency as 10kHz 
  ICR1 =2000000/freq-1;  // ICR1 value, now ICR1=199 when freq=10kHz
  value_temp= ICR1;  //value_temp=199
  
  // Start with both outputs turned off
  OCR1A = 0;
  OCR1B = 0;
  
  // Start the clock
  TCCR1B = 
      TCCR1B 
      |
      (0 << CS12) | (1 << CS11) | (0 << CS10);  // clkI/O/8 (From prescaler)   16000000Hz divided by 8
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite( 9 , !(HIGH )); // set the Pin 9 as Low level
delay( 1 );   // delay 1ms 
digitalWrite( 9 , !(LOW ));  // set the Pin 9 as High level
delay( 3);   // delay 3 ms
}
