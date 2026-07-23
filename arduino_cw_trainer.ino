#include <ctype.h> //toupper(c)
//https://github.com/arduino-libraries/USBHost/blob/master/src/hidboot.h

#include "ecran.h"
#include "keyboard.h"
#include "cw.h"

int mpm(15);//mots par minute 
int freq(700);//Freq.Hz cw
int menu(0);//menu lettres ou lettres + nombres

void setup() {
  initLcd();//initialiser le LCD
  Serial.begin(9600);
  Serial.println("     if (!)Start");

  //keyboard USB init
  if (Usb.Init() == -1) {
    Serial.println("USB init failed");
    while (1) {}
  }


  HidKeyboard.SetReportParser(0, &keyboard_usb);
  delay(500);  
  //nombres aleatoires 
  randomSeed(analogRead(A0));
  nouvelle=true;

  setUpCw(mpm, freq);//Setup CW
}

void loop() {  
  Usb.Task();

  //PRINT SETUP 
  keyboard_usb.printSetup( mpm,freq,menu, correctes,incorrectes);//ligne supérieure

  jeuCW1 (keyboard_usb,mpm, freq, menu);//Fonction qui définit le jeu classique

  
}
