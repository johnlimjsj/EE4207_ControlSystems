
void manualGraph(){
  duty_cycle=0.3; //set frequency as 0.5
  PWM_SET(freq, duty_cycle);  
  delay(500);   // delay 1000 ms
  duty_cycle=0.99;
  PWM_SET(freq, duty_cycle);
  delay(1000);   // delay 1000 ms
}

void stepGraph(){
  duty_cycle = 0;
  increment = 0.2;
  while(1){
//    Serial.println(duty_cycle);
    PWM_SET(freq, duty_cycle);  // Call PWM_SET subprogram
  
    if(duty_cycle >= 1){
      increment = -0.2;
    }
    if(duty_cycle <= 0.05){
      increment = 0.2;
    }
    duty_cycle += increment;
    
    delay(500);
  }
}

float readReturnOutput(int pinNum){
  
  return 5*((float)analogRead(pinNum))/1023;
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

void setDutyCycle(float init_DutyCycle){
  u0 = init_DutyCycle;
  Serial.print(u0);
}

float processPID(float output){
  float error = (setPoint - output)/9.1;
  float corrected = kp*error;
  return corrected + u0;
}

