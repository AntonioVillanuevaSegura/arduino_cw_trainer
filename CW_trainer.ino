#include <ctype.h> //toupper(c)
//https://github.com/arduino-libraries/USBHost/blob/master/src/hidboot.h

#include "ecran.h"
#include "keyboard.h"

int mpm(15);//mots par minute 
int freq(700);//Freq.Hz cw
int menu(0);//menu lettres ou lettres + nombres

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

  printLcd (0,0,"MPM:" +String(mpm)+"   ");
  printLcd (7,0,"F"+String(freq)+"   ");
  printLcd (12,0,"M:"+String(menu)+"   ");
  if (cw.isBuffer()){
    char c=cw.getBuffer()[0];//Get touche
    cw.clearBuffer();

    //MPM MENU
    if (c=='&'){mpm++;c = '\0';}
    if (c==126){mpm--;c = '\0';}

    if (c==35){menu++;c = '\0';}
    if (c==123){menu--;c = '\0';}    

    if (c==40){freq+=10;c = '\0';}
    if (c==45){freq-=10;c = '\0';}   
    if (c!='\0'){
      printLcd (0,1,String(c)+"   ");

    }   

  }
  
}
