#include "Header.h"

int lcdColumns = 20;
int lcdRows = 4;
LiquidCrystal_I2C lcd(0x3F, lcdColumns, lcdRows);

void initLCD() {
  lcd.init();
  lcd.backlight();
  delay(200);
  lcd.clear();
  showLCD("********************", 0, 0);
}

void DisplayDataOnLCD(String na1, String t1, String t2, String t3, String t11, String t22, String t33, String dat, String tim, String ip) {
  lcd.setCursor(0, 2);
  lcd.print(String("TB1: ") + t1 + String(" ") + t2 + String(" ") + t3);

  lcd.setCursor(0, 3);
  lcd.print(String("TB2: ") + t11 + String(" ") + t22 + String(" ") + t33);
}

void showDateIP(String dt) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(String(" ") + dt.substring(0, dt.length() - 3));
  lcd.setCursor(0, 1);
  lcd.print(String(" IP ") + ip);
}

void showLCD(String dt, int row, int col) {
  lcd.setCursor(0, 0);
  lcd.print("********************");
  lcd.setCursor(0, 1);
  lcd.print("*** Initializing ***");
  lcd.setCursor(0, 2);
  lcd.print("** Wait a minutes **"); 
  lcd.setCursor(0, 3);
  lcd.print("********************");
}

void displayLCD(String s, int row, int col){
  lcd.setCursor(0, row);
  lcd.print("                     ");
  lcd.setCursor(col, row);
  lcd.print(s);
}
