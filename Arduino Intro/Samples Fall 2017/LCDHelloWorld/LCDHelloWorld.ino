#include <Adafruit_RGBLCDShield.h>


const char* colorNames[]  = {"RED","GREEN","YELLOW","BLUE","VIOLET","TEAL","WHITE"};
uint8_t     colors[]      = { 0x1 ,  0x2  ,  0x3   ,  0x4 ,  0x5   , 0x6  ,  0x7  };
const char* erraseString  = "       ";
int         option        = 0;



Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

void setup() { 
  
  lcd.begin(16, 2);
  lcd.setCursor(4,0);
  lcd.print("Hello WORLD!!!");

  lcd.setCursor(2,1);
  lcd.print(colorNames[option]);
  lcd.setBacklight(colors[option]);
}

void loop() {
  delay(200);
  lcd.setCursor(2,1);
  uint8_t buttons = lcd.readButtons();

  if((buttons & BUTTON_LEFT) || (buttons & BUTTON_DOWN)){
    option = option - 1;
    if(option < 0) option += 7;    
  } else if((buttons & BUTTON_RIGHT) || (buttons & BUTTON_RIGHT)){
    option = (option+1) % 7;    
  }

  if(buttons){
    lcd.print(erraseString);
    lcd.setCursor(2,1);
    lcd.print(colorNames[option]);
    lcd.setBacklight(colors[option]);
  }
  

}
