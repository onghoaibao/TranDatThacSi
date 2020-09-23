#include <LiquidCrystal_I2C.h>

// set the LCD number of columns and rows
int lcdColumns = 20;
int lcdRows = 4;

// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x3F, lcdColumns, lcdRows);

void setup() {
  // initialize LCD
  lcd.init();
  // turn on LCD backlight
  lcd.backlight();
}

void loop() {
  // set cursor to first column, first row
  lcd.setCursor(0, 0);
  lcd.print("Hello, World!");
  delay(1000);
  lcd.clear();
  
  lcd.setCursor(0, 1);
  lcd.print("Hello, World!");
  delay(1000);
  lcd.clear();
  
  lcd.setCursor(0, 2);
  lcd.print("Hello, World!");
  delay(1000);
  lcd.clear();
  
  lcd.setCursor(0, 3);
  lcd.print("Hello, World!");
  delay(1000);
  lcd.clear();
}
