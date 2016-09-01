int freq = 10000;
float duty_cycle = 0;
int value_temp;
float increment;

float kp, ki;
float setPoint;
float u0;
float output;


void setup() {
  manipulateRegisters();
  setPID(1, 0);
  setSetPoint(3.5);
  setDutyCycle(4/9);
}


void loop() {
  output = 2*readReturnOutput(A0);
  float dutyCycle = processPID(output);
  Serial.println(dutyCycle);
  PWM_SET(10000,dutyCycle);
 
  delay(500);
}



