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




