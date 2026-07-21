#include <ctype.h> //toupper(c)
//https://github.com/arduino-libraries/USBHost/blob/master/src/hidboot.h

#include "ecran.h"
#include "keyboard.h"
#include "cw.h"

int mpm(15);//mots par minute 
int freq(700);//Freq.Hz cw
int menu(0);//menu lettres ou lettres + nombres
//extern char lettre ('/0');
//extern char c('/0');
//extern bool nouvelle(true);//Logique pour une nouvelle lettre CW
//Total des lettres correctes et incorrectes
//#define MAX_JEU 10 //Nombre maximal de lettres par jeu  ou constexpr int MAX = 10; c++11 !!
//extern int totale(0);
//extern int correctes(0);
//extern int incorrectes(0);  

void setup() {
  initLcd();//initialiser le LCD
  Serial.begin(9600);
  Serial.println("     if (!)Start");

  //keyboard USB init
  if (Usb.Init() == -1) {
    Serial.println("USB init failed");
    while (1) {}
  }

  HidKeyboard.SetReportParser(0, &cw);
  delay(500);  
  //nombres aleatoires 
  randomSeed(analogRead(A0));
  nouvelle=true;

  setUpCw(mpm, freq);//Setup CW
}

void loop() {  
  Usb.Task();

  //PRINT SETUP 
  cw.printSetup( mpm,freq,menu, correctes,incorrectes);//ligne supérieure

 jeuCW1 (cw,mpm, freq, menu);

  
}
