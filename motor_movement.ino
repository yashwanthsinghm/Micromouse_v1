
void moveForwardM(int blocks) {
  Serial.println("In move forward fn.\n");
  long currT = micros();
  float deltaT = ((float) (currT - prevT)) / ( 1.0e6 );
  prevT = currT;
  pid[0].setParams(15, 0.5, 0, botSpeed);
  pid[1].setParams(15, 0.5, 0, botSpeed);
  // Read the position
  int pos[NMOTORS];
  do {
    target[0] = blocks * 2062;
    target[1] = blocks * 2062;
    int y = 0;
    int correction;
    int botSpeed_local;

    int RightIR = analogRead(35) / 10; //right
    int LeftIR = analogRead(32) / 10; //LEFT
    if (wallLeft() && wallRight()) {

      y = RightIR - LeftIR;
      y = y / 5;

      //      WebSerial.printf("x = %d,RightIR = %d,LeftIR = %d\n", x, RightIR, LeftIR);
    }
    else if (wallRight()) {
      y = RightIR - 220;
      y = y / 5;
    }
    else if (wallLeft()) {
      y = 220 - LeftIR;
      y = y / 5;
    }
    else
    {

      y = analogRead(35) - analogRead(32);
      if (abs(y) < 200)
      {
        y = y / 10;
      }
      else
      {
        y = 0;
      }
    }
    if ((posi[0] < float(target[0]) * 0.75) || (posi[0] < float(target[0]) - 1000)) {
      botSpeed_local = botSpeed;
    }
    else {
      botSpeed_local = map(target[0] - posi[0], 0, float(target[0]) * 0.25, 50, botSpeed);
    }
    //    int correction = (posi[0] - posi[1]) / 2;
    //    int correction = 0;
    pid[0].setParams(15, 0.5, 0, botSpeed_local  + y);
    pid[1].setParams(15, 0.5, 0, botSpeed_local - y );
    correction = 0;
    noInterrupts(); // disable interrupts temporarily while reading
    for (int k = 0; k < NMOTORS; k++) {
      pos[k] = posi[k];
    }
    interrupts();

    for (int k = 0; k < NMOTORS; k++) {
      // evaluate the control signal
      pid[k].evalu(pos[k], target[k], deltaT, pwr[k], dir[k]);
      //      Serial.print(String(posi[0]));
      //      Serial.print(" ");
      //      Serial.print(String(pwr[0]));
      //      Serial.print(" ");
      //      Serial.print(String(posi[1]));
      //      Serial.print(" ");
      //      Serial.println(String(pwr[1]));
    }
    for (int k = NMOTORS - 1; k >= 0; k--) {
      setMotor(dir[k], pwr[k], motCh[k], in1[k], in2[k]); //pwm[k]
    }
    //    WebSerial.printf("pwr0 = %d, pwr1 = %d\n", pwr[0], pwr[1]);
  } while ((pwr[0] > 30 || pwr[1] > 30) || (posi[0] < target[0] / 2));
  posi[0] = 0;
  posi[1] = 0;
  //  delay(40);
}


void moveBackwardM() {
  Serial.println("In move forward fn.");
  long currT = micros();
  float deltaT = ((float) (currT - prevT)) / ( 1.0e6 );
  prevT = currT;
  pid[0].setParams(15, 0.5, 0, 128);
  pid[1].setParams(15, 0.5, 0, 128);
  // Read the position
  int pos[NMOTORS];
  do {
    target[0] = -458;
    target[1] = -458;
    int correction = (posi[0] - posi[1]) / 2;
    pid[0].setParams(15, 0.5, 0, 128 - correction);
    pid[1].setParams(15, 0.5, 0, 128 + correction);
    noInterrupts(); // disable interrupts temporarily while reading
    for (int k = 0; k < NMOTORS; k++) {
      pos[k] = posi[k];
    }
    interrupts();

    for (int k = 0; k < NMOTORS; k++) {
      // evaluate the control signal
      pid[k].evalu(pos[k], target[k], deltaT, pwr[k], dir[k]);
      //      Serial.print(String(posi[0]));
      //      Serial.print(" ");
      //      Serial.print(String(pwr[0]));
      //      Serial.print(" ");
      //      Serial.print(String(posi[1]));
      //      Serial.print(" ");
      //      Serial.println(String(pwr[1]));
    }
    for (int k = NMOTORS - 1; k >= 0; k--) {
      setMotor(dir[k], pwr[k], motCh[k], in1[k], in2[k]); //pwm[k]
    }
  } while ((pwr[0] > 25 || pwr[1] > 25) || (posi[0] < target[0] / 2));
  posi[0] = 0;
  posi[1] = 0;
  //  delay(100);
}

void moveX(int x) {
  //WebSerial.printf("In moveX fn.\n");
  long currT = micros();
  float deltaT = ((float) (currT - prevT)) / ( 1.0e6 );
  prevT = currT;
  pid[0].setParams(15, 0.5, 0, botSpeed);
  pid[1].setParams(15, 0.5, 0, botSpeed);
  // Read the position
  int pos[NMOTORS];
  do {
    target[0] = x;
    target[1] = x;
    int y = 0;
    //    int correction = 0;
    int RightIR = analogRead(35) / 10; //right
    int LeftIR = analogRead(32) / 10; //LEFT
    int botSpeed_local = 100;

    if (wallLeft() && wallRight()) {

      y = RightIR - LeftIR;
      y = y / 5;
    }
    else if (wallRight()) {
      y = RightIR - 220;
      y = y / 5;
    }
    else if (wallLeft()) {
      y = 220 - LeftIR;
      y = y / 5;
    }
    else
    {
      y = 0;
    }
    //    correction = (posi[0] - posi[1]) / 2;
    //    if (posi[0] < float(target[0]) * 0.25) {
    //      botSpeed_local = botSpeed;
    //    }
    //    else {
    //      botSpeed_local = map(target[0] - posi[0], 0, float(target[0]) * 0.25, 50, botSpeed);
    //    }
    pid[0].setParams(15, 0.5, 0, botSpeed_local + y);
    pid[1].setParams(15, 0.5, 0, botSpeed_local - y);
   // correction = 0;
    noInterrupts(); // disable interrupts temporarily while reading
    for (int k = 0; k < NMOTORS; k++) {
      pos[k] = posi[k];
    }
    interrupts();

    for (int k = 0; k < NMOTORS; k++) {
      // evaluate the control signal
      pid[k].evalu(pos[k], target[k], deltaT, pwr[k], dir[k]);
      //      Serial.print(String(posi[0]));
      //      Serial.print(" ");
      //      Serial.print(String(pwr[0]));
      //      Serial.print(" ");
      //      Serial.print(String(posi[1]));
      //      Serial.print(" ");
      //      Serial.println(String(pwr[1]));
    }
    for (int k = NMOTORS - 1; k >= 0; k--) {
      setMotor(dir[k], pwr[k], motCh[k], in1[k], in2[k]); //pwm[k]
    }
    //    WebSerial.printf("pwr0 = %d, pwr1 = %d\n", pwr[0], pwr[1]);
  } while ((pwr[0] > 20 || pwr[1] > 20) || (posi[0] < target[0] / 2));
  posi[0] = 0;
  posi[1] = 0;
  //  delay(30);
}


void moveNinty() {
  moveX(430);
  long currT = micros();
  float deltaT = ((float) (currT - prevT)) / ( 1.0e6 );
  prevT = currT;
  pid[0].setParams(15, 0.2, 0, 87);
  pid[1].setParams(15, 0.2, 0, 150);
  // Read the position
  int pos[NMOTORS];
  do {
    target[0] = 2214;
    target[1] = 3834;
    noInterrupts(); // disable interrupts temporarily while reading
    for (int k = 0; k < NMOTORS; k++) {
      pos[k] = posi[k];
    }
    interrupts();

    for (int k = 0; k < NMOTORS; k++) {
      // evaluate the control signal
      pid[k].evalu(pos[k], target[k], deltaT, pwr[k], dir[k]);
      //      Serial.print(String(posi[0]));
      //      Serial.print(" ");
      //      Serial.print(String(pwr[0]));
      //      Serial.print(" ");
      //      Serial.print(String(posi[1]));
      //      Serial.print(" ");
      //      Serial.println(String(pwr[1]));
    }
    for (int k = NMOTORS - 1; k >= 0; k--) {
      setMotor(dir[k], pwr[k], motCh[k], in1[k], in2[k]); //pwm[k]
    }
  } while ((pwr[0] > 20 || pwr[1] > 20) || (posi[0] < target[0] / 2));
  posi[0] = 0;
  posi[1] = 0;
  delay(30);
}
void moveNintyLeft() {
  moveX(430);
  long currT = micros();
  float deltaT = ((float) (currT - prevT)) / ( 1.0e6 );
  prevT = currT;
  pid[1].setParams(15, 0.2, 0, 87);
  pid[0].setParams(15, 0.2, 0, 150);
  // Read the position
  int pos[NMOTORS];
  do {
    target[1] = 2214;
    target[0] = 3834;
    noInterrupts(); // disable interrupts temporarily while reading
    for (int k = 0; k < NMOTORS; k++) {
      pos[k] = posi[k];
    }
    interrupts();

    for (int k = 0; k < NMOTORS; k++) {
      // evaluate the control signal
      pid[k].evalu(pos[k], target[k], deltaT, pwr[k], dir[k]);
      //      Serial.print(String(posi[0]));
      //      Serial.print(" ");
      //      Serial.print(String(pwr[0]));
      //      Serial.print(" ");
      //      Serial.print(String(posi[1]));
      //      Serial.print(" ");
      //      Serial.println(String(pwr[1]));
    }
    for (int k = NMOTORS - 1; k >= 0; k--) {
      setMotor(dir[k], pwr[k], motCh[k], in1[k], in2[k]); //pwm[k]
    }
  } while ((pwr[0] > 20 || pwr[1] > 20) || (posi[0] < target[0] / 2));
  posi[0] = 0;
  posi[1] = 0;
  delay(30);
}





void turnRightM() {
  // moveX(292);
  long currT = micros();
  float deltaT = ((float) (currT - prevT)) / ( 1.0e6 );
  prevT = currT;
  pid[0].setParams(15, 0.5, 0, 140);
  pid[1].setParams(15, 0.5, 0, 140);
  // Read the position
  int pos[NMOTORS];
  do {
    target[0] = -765;//765
    target[1] = 765;//765
    noInterrupts(); // disable interrupts temporarily while reading
    for (int k = 0; k < NMOTORS; k++) {
      pos[k] = posi[k];
    }
    interrupts();

    for (int k = 0; k < NMOTORS; k++) {
      // evaluate the control signal
      pid[k].evalu(pos[k], target[k], deltaT, pwr[k], dir[k]);
      //      Serial.print(String(posi[0]));
      //      Serial.print(" ");
      //      Serial.print(String(pwr[0]));
      //      Serial.print(" ");
      //      Serial.print(String(posi[1]));
      //      Serial.print(" ");
      //      Serial.println(String(pwr[1]));
    }
    for (int k = NMOTORS - 1; k >= 0; k--) {
      setMotor(dir[k], pwr[k], motCh[k], in1[k], in2[k]); //pwm[k]
    }

  } while ((pwr[0] > 20 || pwr[1] > 20) || (posi[1] < target[1] / 2));
  posi[0] = 0;
  posi[1] = 0;
  delay(50);
}

void turnLeftM() {
  //WebSerial.printf("In left turn motor movement");
  //   moveX(292);
  long currT = micros();
  float deltaT = ((float) (currT - prevT)) / ( 1.0e6 );
  prevT = currT;
  pid[0].setParams(15, 0.5, 0, 140);
  pid[1].setParams(15, 0.5, 0, 140);
  // Read the position
  int pos[NMOTORS];
  do {
    target[0] = 765;
    target[1] = -765;
    noInterrupts(); // disable interrupts temporarily while reading
    for (int k = 0; k < NMOTORS; k++) {
      pos[k] = posi[k];
    }
    interrupts();

    for (int k = 0; k < NMOTORS; k++) {
      // evaluate the control signal
      pid[k].evalu(pos[k], target[k], deltaT, pwr[k], dir[k]);
      //      Serial.print(String(posi[0]));
      //      Serial.print(" ");
      //      Serial.print(String(pwr[0]));
      //      Serial.print(" ");
      //      Serial.print(String(posi[1]));
      //      Serial.print(" ");
      //      Serial.println(String(pwr[1]));
    }
    for (int k = NMOTORS - 1; k >= 0; k--) {
      setMotor(dir[k], pwr[k], motCh[k], in1[k], in2[k]); //pwm[k]
    }

  } while ((pwr[0] > 20 || pwr[1] > 20) || (posi[0] < target[0] / 2));
  posi[0] = 0;
  posi[1] = 0;
  delay(50);
}

void turn180M() {
  // moveX(292);
  long currT = micros();
  float deltaT = ((float) (currT - prevT)) / ( 1.0e6 );
  prevT = currT;
  pid[0].setParams(15, 0.5, 0, 128);
  pid[1].setParams(15, 0.5, 0, 128);
  // Read the position
  int pos[NMOTORS];
  do {
    target[0] = -1530;//-1530
    target[1] = 1530;//1530
    noInterrupts(); // disable interrupts temporarily while reading
    for (int k = 0; k < NMOTORS; k++) {
      pos[k] = posi[k];
    }
    interrupts();

    for (int k = 0; k < NMOTORS; k++) {
      // evaluate the control signal
      pid[k].evalu(pos[k], target[k], deltaT, pwr[k], dir[k]);
      //      Serial.print(String(posi[0]));
      //      Serial.print(" ");
      //      Serial.print(String(pwr[0]));
      //      Serial.print(" ");
      //      Serial.print(String(posi[1]));
      //      Serial.print(" ");
      //      Serial.println(String(pwr[1]));
    }
    for (int k = NMOTORS - 1; k >= 0; k--) {
      setMotor(dir[k], pwr[k], motCh[k], in1[k], in2[k]); //pwm[k]
    }

  } while ((pwr[0] > 20 || pwr[1] > 20) || (posi[1] < target[1] / 2));
  posi[0] = 0;
  posi[1] = 0;
  delay(100);
}

void moveSharpOneEightyLeft() {
  moveX(292);
  long currT = micros();
  float deltaT = ((float) (currT - prevT)) / ( 1.0e6 );
  prevT = currT;
  pid[0].setParams(15, 0.5, 0, 128);
  pid[1].setParams(15, 0.5, 0, 128);
  // Read the position
  int pos[NMOTORS];
  do {
    target[0] = 1620;
    target[1] = -1620;
    noInterrupts(); // disable interrupts temporarily while reading
    for (int k = 0; k < NMOTORS; k++) {
      pos[k] = posi[k];
    }
    interrupts();

    for (int k = 0; k < NMOTORS; k++) {
      // evaluate the control signal
      pid[k].evalu(pos[k], target[k], deltaT, pwr[k], dir[k]);
      //      Serial.print(String(posi[0]));
      //      Serial.print(" ");
      //      Serial.print(String(pwr[0]));
      //      Serial.print(" ");
      //      Serial.print(String(posi[1]));
      //      Serial.print(" ");
      //      Serial.println(String(pwr[1]));
    }
    for (int k = NMOTORS - 1; k >= 0; k--) {
      setMotor(dir[k], pwr[k], motCh[k], in1[k], in2[k]); //pwm[k]
    }

  } while ((pwr[0] > 20 || pwr[1] > 20) || (posi[0] < target[0] / 2));
  posi[0] = 0;
  posi[1] = 0;
  //  delay(300);
}



void moveOneEighty() {
  moveX(584);
  long currT = micros();
  float deltaT = ((float) (currT - prevT)) / ( 1.0e6 );
  prevT = currT;
  pid[0].setParams(15, 0.5, 0, 50);
  pid[1].setParams(15, 0.5, 0, 150);
  // Read the position
  int pos[NMOTORS];
  do {
    target[0] = 1620;
    target[1] = 4861;
    noInterrupts(); // disable interrupts temporarily while reading
    for (int k = 0; k < NMOTORS; k++) {
      pos[k] = posi[k];
    }
    interrupts();

    for (int k = 0; k < NMOTORS; k++) {
      // evaluate the control signal
      pid[k].evalu(pos[k], target[k], deltaT, pwr[k], dir[k]);
      //      Serial.print(String(posi[0]));
      //      Serial.print(" ");
      //      Serial.print(String(pwr[0]));
      //      Serial.print(" ");
      //      Serial.print(String(posi[1]));
      //      Serial.print(" ");
      //      Serial.println(String(pwr[1]));
    }
    for (int k = NMOTORS - 1; k >= 0; k--) {
      setMotor(dir[k], pwr[k], motCh[k], in1[k], in2[k]); //pwm[k]
    }

  } while ((pwr[0] > 20 || pwr[1] > 20) || (posi[0] < target[0] / 2));
  posi[0] = 0;
  posi[1] = 0;
  //delay(300);
}


//template <int j>
void readEncoder1() {
  int MSB = digitalRead(enca[0]); //MSB = most significant bit
  int LSB = digitalRead(encb[0]); //LSB = least significant bit

  int encoded = (MSB << 1) | LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded[0] << 2) | encoded; //adding it to the previous encoded value

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) posi[0]--;
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) posi[0]++;

  lastEncoded[0] = encoded; //store this value for next time
  //      Serial.println(posi[0]);
}

void readEncoder2() {
  int MSB = digitalRead(enca[1]); //MSB = most significant bit
  int LSB = digitalRead(encb[1]); //LSB = least significant bit

  int encoded = (MSB << 1) | LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded[1] << 2) | encoded; //adding it to the previous encoded value

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) posi[1]--;
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) posi[1]++;

  lastEncoded[1] = encoded; //store this value for next time
  //      Serial.println(posi[1]);
}


void setMotor(int dir, int pwmVal, int pwm, int in1, int in2) {
  ledcWrite(pwm, pwmVal);
  if (dir == 1) {
    digitalWrite(sty, HIGH);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
  else if (dir == -1) {
    digitalWrite(sty, HIGH);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }
  else {
    digitalWrite(sty, LOW);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
}
