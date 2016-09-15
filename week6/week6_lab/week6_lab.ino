#define TIMEINMS 500
int value_temp;
int freq = 10000;
unsigned long lastTime;
double input, Output, setPoint;
double err_sum, lastErr;
double kp, ki;
float u0, K;
float duty_cycle, increment;
int SampleTime = 10; //1 sec


void setup() {
  setupRegisters();
  SetTunings(1.10, 0.01);
  SetSampleTime(10);
  setu0(4, 9.1);
  PWM_SET(10000,u0);
  delay(1000);

}

void loop() {
  setSetPoint(3.5);
  processOutAndPID(A0);
  setSetPoint(4.5);
  processOutAndPID(A0);

}



inline void processOutAndPID(int pinNum){
  for(int i=0; i<10000; i++){
    unsigned long now = millis();
    int timeChange = (now - lastTime);
    if(timeChange>=SampleTime)
    {
      double input = 10*((float)analogRead(pinNum))/1023;
      double error = (setPoint - input);
      err_sum += error;
      Output = (kp*error + ki*err_sum)/K + setPoint/K;

      if(Output>1){ Output=1; }
      if(Output<0){ Output=0; }
      lastTime = now;
      
      
    }
    PWM_SET(10000, Output);
  }
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

void SetTunings(double Kp, double Ki)
{
  double SampleTimeInSec = ((double)SampleTime)/1000;
   kp = Kp;
   ki = Ki * SampleTimeInSec;
}

void SetSampleTime(int NewSampleTime)
{
   if (NewSampleTime > 0)
   {
      double ratio  = (double)NewSampleTime/ (double)SampleTime;
      ki *= ratio;

      SampleTime = (unsigned long)NewSampleTime;
   }
}




