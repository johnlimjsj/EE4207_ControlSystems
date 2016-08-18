int freq = 10000;
float duty_cycle = 0;
int value_temp;
float increment;

//  The PWM subprogram
 void  PWM_SET(int freq, float duty_cycle)
 {
  ICR1 =2000000/freq-1;  // ICR1, the Input Capture Register，
  value_temp= ICR1; 
  OCR1A = duty_cycle*value_temp;   //  Pin 9 is the output, OCR1A range: 0 to value_temp;. duty cycle： between 0 (always off) and value_temp (always on)..
  }

void setup() {
  Serial.begin(9600);
   // Turn off the timer while we make changes
  TCCR1B = TCCR1B & ~ ((1 << CS12) | (1 << CS11) | (1 << CS10));   // Timer/Counter Control Registers (TCCR1A/B);  CS: Clock Select
  // Ensure the Timer 1 output pins are configured for output
  pinMode( 9, OUTPUT );  // Pin 9 is the output
  pinMode( 10, OUTPUT ); // Pin 10 is the output
  // Set Compare Output Mode and part of the Waveform Generation Mode (mode 14)
  TCCR1A =                                                                           // Timer/Counter Control Registers (TCCR1A/B), details can be found in Chapter 16.11.1
      (1 << COM1A1) | (0 << COM1A0)  // Clear OC1A on Compare Match, set OC1A at BOTTOM (non-inverting mode)
      |
      (1 << COM1B1) | (1 << COM1B0)  // Set OC1B on Compare Match, clear OC1B at BOTTOM (inverting mode)
      |
      (1 << WGM11) | (0 << WGM10);  // Mode 14: Fast PWM, TOP = ICR1, Update of OCR1x at BOTTOM, TOV1 Flag Set on TOP;    WGM: Waveform Generation mode

  // Set the other half of the Waveform Generation Mode (mode 14) and ensure a few things are disabled
  TCCR1B =                                                        // details can be found in Chapter 16.11.2
      (0 << ICNC1)  // Input Capture Noise Canceler disabled
      |
      (0 << ICES1)  // Input Capture Edge Select don't care
      |
      (1 << WGM13) | (1 << WGM12)  // Mode 14: Fast PWM, TOP = ICR1, Update of OCR1x at BOTTOM, TOV1 Flag Set on TOP
      |
      (0 << CS12) | (0 << CS11) | (0 << CS10);  // Clock continues to be disabled.  Not yet finished configuring.
  // Set the output frequency
  // fOCnxPWM = fclk_I/O / (N * (1 + TOP))
  // fOCnxPWM = 16000000 / (8 * (1 + ICR1))
 // Start with both outputs turned off
  OCR1A = 0;   // Output Compare Registers (OCR1A/B)
  OCR1B = 0; 
  // Start the clock
  TCCR1B = 
      TCCR1B 
      |
      (0 << CS12) | (1 << CS11) | (0 << CS10);  // clkI/O/8 (From prescaler)     16000000Hz divided by 8
}


void loop() {
  
  manualGraph();
}

void manualGraph(){
  duty_cycle=0.3; //set frequency as 0.5
  PWM_SET(freq, duty_cycle);  
  delay(500);   // delay 1000 ms
  duty_cycle=0.7;
  PWM_SET(freq, duty_cycle);
  delay(1000);   // delay 1000 ms
}

void stepGraph(){
  duty_cycle = 0;
  increment = 0.2;
  while(1){
    Serial.println(duty_cycle);
    PWM_SET(freq, duty_cycle);  // Call PWM_SET subprogram
  
    if(duty_cycle >= 1){
      increment = -0.2;
    }
    if(duty_cycle <= 0){
      increment = 0.2;
    }
    duty_cycle += increment;
    
    delay(500);
  }
}

