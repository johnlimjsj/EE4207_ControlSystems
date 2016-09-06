int freq = 10000;
float duty_cycle = 0;
int value_temp;
float increment;

float kp, ki;
float setPoint;
float u0;
float output;
int timeInMs = 2000;

void setup() {
  
  manipulateRegisters();
  setPID(0.1, 0);
  setu0(0.5);
  Serial.println(u0);
}


void loop() {

  uint32_t start=millis();
  setSetPoint(4);
  while(millis() - start < timeInMs){
    controlLoop();
  }

  start=millis();
  setSetPoint(5);
  while(millis() - start < timeInMs){
    controlLoop();
  }

}


void controlLoop(){
  output = 2*readReturnOutput(A0);
  float dutyCycle = processPID(output);
  PWM_SET(10000,dutyCycle);
}


