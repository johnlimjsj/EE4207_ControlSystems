

void setSetPoint(float sp){
  setPoint = sp;
}

void setu0(float y0, float _K){
  K = _K;
  u0 = y0/_K;
  Serial.print(u0);
}




