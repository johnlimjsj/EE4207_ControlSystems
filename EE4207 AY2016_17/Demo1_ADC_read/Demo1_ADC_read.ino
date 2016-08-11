int _ABVAR_1_val;
void setup() {
  // put your setup code here, to run once:
_ABVAR_1_val = 0;     //set _ABVAR_1_val as 0 
Serial.begin(9600);   //Sets the data rate in bits per second (baud) for serial data transmission. 
}

void loop() {
  // put your main code here, to run repeatedly:
_ABVAR_1_val = analogRead(A0) ;// "analogRead" is the function for I/O to read.  Read ADC value from Pin A0.   The range is 0 to 1023.
Serial.print( "Value=" );  // print the word "Value"
Serial.print( _ABVAR_1_val );  // print the result of "_ABVAR_1_val".
Serial.println("");            // equal to "enter" and "line break"
delay( 100 );                   // 100 milliseconds.

}
