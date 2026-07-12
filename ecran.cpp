#include "ecran.h"

LiquidCrystal_I2C lcd(0x27, cols, lignes);

void initLcd() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("F4LEC");
}

void printLcd(int x,int y,String txt){
  lcd.setCursor(x, y);
  lcd.print(txt);
}

