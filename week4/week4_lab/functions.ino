
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


float computeError(float output){
  return (setPoint - output);
}
void setPID(float setKp, float setKi){
  kp = setKp;
  ki = setKi;
}

void setSetPoint(float sp){
  setPoint = sp;
}

void setu0(float y0, float _K){
  K = _K;
  u0 = y0/_K;
  Serial.print(u0);
}




