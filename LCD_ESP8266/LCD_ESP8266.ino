#include <LiquidCrystal_I2C.h>
long duration, distance; // Duration used to calculate distance
// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;
// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);
void setup(){
  lcd.begin(5, 4);// initialize LCD
  lcd.init();
  // turn on LCD backlight
  lcd.backlight();
}
void loop(){
  //print welcome screen
  lcd.setCursor(0,0);
  lcd.print("GISA KAZE");
  lcd.setCursor(0,1);
  lcd.print("FREDISON");
  //code to detect distance
  lcd.clear();
  delayMicroseconds(10);
}
