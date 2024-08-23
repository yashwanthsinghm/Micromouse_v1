void pathChange(int curr_x, int curr_y) {
  if (existInPath(curr_y * 16 + curr_x)) {
    int temp = checkCounter(curr_y * 16 + curr_x);
    counter = temp + 1;
  }
  else {
    path[counter] = curr_y * 16 + curr_x;
    counter++;
  }
}

bool existInPath(int num) {
  for (int i = 0; i < counter; i++) {
    if (path[i] == num ) {
      return true;
    }
  }
  return false;
}

int checkCounter(int num) {
  for (int i = 0; i < counter; i++) {
    if (path[i] == num) {
      return i;
    }
  }
}

void copyFromEEPROM()
{
  //EEPROM.commit();
 // WebSerial.printf("copyFromEEPROM");
  for (short i = 0; i < EEPROM_SIZE; i++)
  {
    //    EEPROM.commit();
    path[i] =  EEPROM.read(i);
  //  WebSerial.printf("EEPROM path[i]=%d\n", path[i]);
      delay(100);
  }
  delay(100);
//  counter =  EEPROM.read(150);
//  WebSerial.printf("EEPROM counter=%d\n", counter);

}


void copyToEEPROM()
{
  //WebSerial.printf("copyToEEPROM");
  for (short i = 0; i < EEPROM_SIZE; i++)
  {
    delay(100);
    EEPROM.write(i, path[i]) ;
    EEPROM.commit();
  //  WebSerial.printf("path[i]=%d\n", path[i]);
  }
  delay(100);
//     WebSerial.printf("counter before copying %d\n", counter);
//  WebSerial.printf("copyCounterToEEPROM");
//  EEPROM.write(150, counter) ;
//  EEPROM.commit();

}
