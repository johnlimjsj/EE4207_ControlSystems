#define TIMEINMS 500

int freq = 10000;
float duty_cycle = 0;
int value_temp;
float increment;

float kp, ki;
float setPoint;
float u0, K;
float output;
float err_sum = 0;
uint32_t start;

void setup() {
  setupRegisters();
  setPID(0.3, 0.01);
  setu0(4, 9.1);
  setSetPoint(3.5);
  PWM_SET(10000,u0);
}

void loop() {
  setSetPoint(3.5);
  controlPidLoop();

  setSetPoint(4.5);
  controlPidLoop();
}

inline void controlPidLoop(){
  start=millis();
  while(millis() - start < TIMEINMS){
    float dutyCycle = processOutAndPID(A0);
    PWM_SET(10000,dutyCycle);
  }
}

inline float processOutAndPID(int pinNum){
  float output = 10*((float)analogRead(pinNum))/1023;
  float error = (setPoint - output);
  err_sum += error;
  float delta_u = (kp*error + ki*err_sum)/K;
  return delta_u + output/K;
}


