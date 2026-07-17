#include <ctype.h> //toupper(c)
//https://github.com/arduino-libraries/USBHost/blob/master/src/hidboot.h

#include "ecran.h"
#include "keyboard.h"
#include "cw.h"

int mpm(15);//mots par minute 
int freq(700);//Freq.Hz cw
int menu(0);//menu lettres ou lettres + nombres
char lettre ('/0');
char c('/0');
bool nouvelle(true);

void setup() {
  initLcd();//initialiser le LCD
  Serial.begin(9600);
  Serial.println("Start");

  //keyboard USB init
  if (Usb.Init() == -1) {
    Serial.println("USB init failed");
    while (1) {}
  }
  HidKeyboard.SetReportParser(0, &cw);
  //nombres aleatoires 
  randomSeed(analogRead(A0));
  nouvelle=true;

}

void loop() {  
  //printLcd(0,0,"FFFFxx");
  Usb.Task();
  //Debug KEYBOARD LCD
 /*
  if (cw.isBuffer()){
    char c =cw.getBuffer()[0];
    cw.clearBuffer();
    printLcd (0,0,String (c));
    printLcd(0, 1, String((unsigned char) (c ))); // Más legible y equivalent
    Serial.println((unsigned char) (c ));
  
  }
  */

  //PRINT SETUP 
  printLcd (0,0,"MPM:" +String(mpm)+"   ");
  printLcd (7,0,"F"+String(freq)+"   ");
  printLcd (12,0,"M:"+String(menu)+"   ");

  //printLcd (5,1,String (letreAleatorie(26))+"   ");

  //Lettre Aleatoire , getCwCode, and playCW
  if (nouvelle){
   lettre=*letreAleatorie(26);//Lecture d'une lettre aleatoire 
   playCW  (getCwCode(lettre));
  
   printLcd (5,1,String (lettre)+"   ");//Debug
   nouvelle=false;

  }
  

  //while(!cw.isBuffer()){//Tant qu’aucune lettre n’est appuyée, il reste dans la boucle

    if (cw.isBuffer()){//Une touche a été appuyée ?

      c=cw.getBuffer()[0];//Get touche
      cw.clearBuffer();

      //MPM MENU FREQ
      if (c=='&'){mpm++;c = '\0';} //1 &
      if (c==126){mpm--;c = '\0';} //2 ~

      if (c==35){menu++;c = '\0';} //3 #
      if (c==123){menu--;c = '\0';} //4 {  

      if (c==40){freq+=10;c = '\0';} //5 (
      if (c==45){freq-=10;c = '\0';} //6 -

      if (c!='\0'){//PRINT TOUCHE LIGNE 1
        printLcd (0,1,String(c)+"   ");
      }  

      if (c==lettre){
        nouvelle=true;
      }


    }

  //}
  
}
