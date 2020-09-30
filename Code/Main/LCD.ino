#include "Header.h"

int lcdColumns = 20;
int lcdRows = 4;
LiquidCrystal_I2C lcd(0x3F, lcdColumns, lcdRows);

void initLCD(){
  lcd.init();
  lcd.backlight();
}

void DisplayDataOnLCD(String namt1, String namt2, String t1, String t2, String t3, String t11, String t22, String t33, String dat, String tim){
  lcd.setCursor(0, 0);
  lcd.print("Date: " + dat);
  
  lcd.setCursor(0, 1);
  lcd.print("Time: " + tim);

  lcd.setCursor(0, 2);
  lcd.print(namt1 + ": " + t1 + " " + t2 + " " + t3);
  
  lcd.setCursor(0, 3);
  lcd.print(namt2 + ": " + t11 + " " + t22 + " " + t33);
}
