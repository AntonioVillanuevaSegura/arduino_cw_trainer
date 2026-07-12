#ifndef ECRAN_H
#define ECRAN_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define cols 16
#define lignes 2

extern LiquidCrystal_I2C lcd;
/*
GND               BLACK
VCC               WHITE1
SDA ----> A5(19)  GRAY
SCL ----> A4(18)  WHITE2
*/
// Broche 18 (A4) , SDA Broche 19 (A5) - SCL
//LCD 1602A I2C https://docs.arduino.cc/libraries/liquidcrystal-i2c/
void  initLcd();
void printLcd(int x,int y ,String txt);

#endif