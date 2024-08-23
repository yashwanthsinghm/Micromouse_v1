void motor_setup()
{
  ledcSetup(motCh[0], freq, resolution);
  ledcSetup(motCh[1], freq, resolution);
  ledcAttachPin(pwm[0], motCh[0]);
  ledcAttachPin(pwm[1], motCh[1]);

  for (int k = 0; k < NMOTORS; k++) {
    pinMode(enca[k], INPUT);
    pinMode(encb[k], INPUT);
    pinMode(in1[k], OUTPUT);
    pinMode(in2[k], OUTPUT);
    pid[k].setParams(15, 0.5, 0, 128);

  }
  pinMode(sty, OUTPUT);
  digitalWrite(sty, HIGH);
  attachInterrupt(digitalPinToInterrupt(enca[0]), readEncoder1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encb[0]), readEncoder1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(enca[1]), readEncoder2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encb[1]), readEncoder2, CHANGE);
}

void pcb_setup() {
  pinMode(expMode, INPUT_PULLUP);
  pinMode(expLED, OUTPUT);
  attachInterrupt(expMode, modeChange, FALLING);
//  attachInterrupt(speedButton, speedChange, RISING);
  
}

bool wallFront() {
  if ( analogRead(34) < 1500) {
    return false ;
  }
  else {
    return true;
  }
}

bool wallRight() {
  if ( analogRead(35) < 1400) {
    return false ;
  }
  else {
    return true;
  }
}

bool wallLeft() {
  if ( analogRead(32) < 1400) {
    return false ;
  }
  else {
    return true;
  }
}

void modeChange() {
  exploration = !(exploration);
  if(exploration) {
    digitalWrite(expLED, LOW);
  }
  else {
    digitalWrite(expLED, HIGH);
  }
}
//
//void speedChange() {
//  chSpeed = 1;
//  botSpeed += 2;
//}
