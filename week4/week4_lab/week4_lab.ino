#define TIMEINMS 500

int freq = 30000;
float duty_cycle = 0;
int value_temp;
float increment;

float kp, ki;
float setPoint;
float u0, K;
float output;
float err_sum = 0, error, prev_error, delta_u, prev_u=0,  u;
uint32_t start;

void setup() {
  setupRegisters();
  setPID(0.60, 0.03);
  setu0(4, 9.1);
  PWM_SET(10000,u0);
  delay(1000);
  u=u0;
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
  error = (setPoint - output);
  err_sum += error;
  delta_u = (kp*error + ki*err_sum)/K;
  u = delta_u + u0;
  if(u>1){ u=1; }
  if(u<0){ u=0; }
  prev_u = u;
  return u;
}


void manualGraph(){
  duty_cycle=0.2; //set frequency as 0.5
  PWM_SET(freq, duty_cycle);  
  delay(500);   // delay 1000 ms
  duty_cycle=0.8;
  PWM_SET(freq, duty_cycle);
  delay(500);   // delay 1000 ms
}

void stepGraph(int delayTime, float stepSize){
  duty_cycle = 0;
  increment = stepSize;
  while(1){
    PWM_SET(freq, duty_cycle);  // Call PWM_SET subprogram
    if(duty_cycle >= 1){increment = -stepSize;}
    if(duty_cycle <= 0.0){increment = stepSize; }
    duty_cycle += increment;
    delay(delayTime);
    PWM_SET(freq, 1);
    delay(delayTime);
  }
}


