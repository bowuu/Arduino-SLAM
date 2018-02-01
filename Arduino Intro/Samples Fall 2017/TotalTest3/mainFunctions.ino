bool checkReset(){
  return lcd.readButtons() & BUTTON_SELECT;
}

bool movementTest(){
  if (checkReset()) {
    LServo.writeMicroseconds(1500); 
    RServo.writeMicroseconds(1500);
    return true;
  }
  uint8_t buttons = lcd.readButtons();

  if(buttons) lcd.setCursor(2,1);

  switch( buttons){
    case BUTTON_UP: 
    {
      lcd.print("Forward ");
      LServo.writeMicroseconds(1600); 
      RServo.writeMicroseconds(1400);
      break; 
      
    } case BUTTON_DOWN: {
      lcd.print("Backward");
      LServo.writeMicroseconds(1400); 
      RServo.writeMicroseconds(1600);
      break;
      
    } case BUTTON_LEFT: {
      
      lcd.print("Left    ");
      LServo.writeMicroseconds(1520); 
      RServo.writeMicroseconds(1400); 
      break;
      
    } case BUTTON_RIGHT: {
  
      lcd.print("Right    ");
      LServo.writeMicroseconds(1600); 
      RServo.writeMicroseconds(1480); 
      break;
      
    }
  }
  
  return false;
}


int readingSensor = SF;

void sensorTestSetup(){
  readingSensor = SF;
  lcd.setCursor(2,1);
  lcd.print("Front ");
}

bool sensorTest(){
 
  if ( checkReset()) {
    readingSensor = SF;
    return true;
  }

  uint8_t buttons = lcd.readButtons();
  
  if(buttons) lcd.setCursor(2,1);
  switch( buttons){
    case BUTTON_UP: 
    {
      lcd.print("Front ");
      readingSensor = SF;
      break; 
      
    } case BUTTON_DOWN: {
      lcd.print("Long  ");
      readingSensor = SG;
      break;
      
    } case BUTTON_LEFT: {
      
      lcd.print("Left  ");
      readingSensor = SL;
      break;
      
    } case BUTTON_RIGHT: {
  
      lcd.print("Right ");
      readingSensor = SR;
      break;
      
    }
  }

  if(buttons) {
    int value = analogRead(readingSensor);
    lcd.setCursor(10,1);
    lcd.print("     ");
    lcd.setCursor(10,1);
    lcd.print(value);
    delay(70);
  }


  delay(30);
  return false;
}

unsigned long lEncCount = 0;
unsigned long rEncCount = 0;
unsigned long lEncLast = 0;
unsigned long rEncLast = 0;

void encoderTestSetup(){
  lEncCount = 0;
  rEncCount = 0;
}

bool encoderTest(){

  if(checkReset()) {
    LServo.writeMicroseconds(1500); 
    RServo.writeMicroseconds(1500); 
    return true;
  }
    
  /***** Encoders ******/    
  if (lEncCount < 300 || rEncCount < 300){
    LServo.writeMicroseconds(1520); 
    RServo.writeMicroseconds(1480); 
  } else {
    LServo.writeMicroseconds(1500); 
    RServo.writeMicroseconds(1500); 
    return true;
  }

  int lEncVal = digitalRead(lEncPin);
  int rEncVal = digitalRead(rEncPin);
  
  if (lEncVal != lEncLast) lEncCount++;
  if (rEncVal != rEncLast) rEncCount++;

  if ( lEncVal != lEncLast || rEncVal != rEncLast ){
    if (lEncCount % 10 == 0 || rEncCount % 10 == 0){
      lcd.setCursor(0,1);
      lcd.print("                ");

      lcd.setCursor(1,1);
      lcd.print(lEncCount);
  
      lcd.setCursor(7,1);
      lcd.print(rEncCount); 
    }      
    
  }
  lEncLast = lEncVal;
  rEncLast = rEncVal;

  delay(15);
  return false;  
}

bool colorSensorTest(){
  //lcd.clear();

  if(checkReset()) {
    return true;
  }

  uint8_t buttons = lcd.readButtons();

  if(buttons){
    lcd.setCursor(0,1);
    lcd.print("                ");
  
    // Setting red filtered photodiodes to be read
    digitalWrite(S2,LOW);
    digitalWrite(S3,LOW);
    lcd.setCursor(1,1);
    int fRed = pulseIn(sensorOut, LOW);
    lcd.print(fRed);
  
    // Setting Green filtered photodiodes to be read
    digitalWrite(S2,HIGH);
    digitalWrite(S3,HIGH);
    lcd.setCursor(5,1);
    int fGreen = pulseIn(sensorOut, LOW);
    lcd.print(fGreen);
  
    // Setting Blue filtered photodiodes to be read
    digitalWrite(S2,LOW);
    digitalWrite(S3,HIGH);
    lcd.setCursor(9,1);
    int fBlue = pulseIn(sensorOut, LOW);
    lcd.print(fBlue);
  
    Serial.print(fRed);
    Serial.print(" ");
    Serial.print(fGreen);
    Serial.print(" ");
    Serial.print(fBlue);
    Serial.print("\n");
    delay(70);
  }

  delay(30);
  return false;
}
