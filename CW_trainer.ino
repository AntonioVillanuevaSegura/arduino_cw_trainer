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
bool nouvelle(true);//Logique pour une nouvelle lettre CW
//Total des lettres correctes et incorrectes
#define MAX_JEU 10 //Nombre maximal de lettres par jeu  ou constexpr int MAX = 10; c++11 !!
int totale(0);
int correctes(0);
int incorrectes(0);  


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
  //nombres aleatoires 
  randomSeed(analogRead(A0));
  nouvelle=true;

  setUpCw(mpm, freq);//Setup CW

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
  printLcd (2,1,String (correctes)+":"+String (incorrectes)+"  ");

  //Lettre Aleatoire obtien le code CW  getCwCode et playCW
  //Génère une lettre aléatoire que nous devons devine et Émets le CW
  if (nouvelle){
   //printLcd (0,1,"                 ");
   lettre=*letreAleatorie(26);//Lecture d'une lettre aleatoire 
   playCW  (getCwCode(lettre));
  
   printLcd (9,1,String (lettre)+"  ");//DEBUG random
   nouvelle=false;
   printLcd (10,1,"      ");
   totale++;//une nouvelle lettre

  }
  while (!cw.isBuffer()){Usb.Task();}

    if (cw.isBuffer()){//Une touche a été appuyée ?
      printLcd (9,1,"        ");

      c=cw.getBuffer()[0];//Get touche
      cw.clearBuffer();

      //MPM MENU FREQ
      if (c=='&'){mpm++;c = '\0'; setUpCw(mpm, freq);} //1 &
      if (c==126){mpm--;c = '\0'; setUpCw(mpm, freq);} //2 ~

      if (c==35){menu++;c = '\0';} //3 #
      if (c==123){menu--;c = '\0';} //4 {  

      if (c==40){freq+=10;c = '\0'; setUpCw(mpm, freq);} //5 (
      if (c==45){freq-=10;c = '\0'; setUpCw(mpm, freq);} //6 -

      if (c!='\0'){//PRINT TOUCHE LIGNE 1
        printLcd (0,1,String(c)+" ");
      }  

      if (c==lettre){
        nouvelle=true;
        printLcd (10,1,"OK  !");
        correctes++;
      }else if (c!='\0'){
        printLcd (10,1,"NON !");
        erreurTone();
        printLcd (10,1,"      ");

        playCW  (getCwCode(lettre));//Erreur rePlay CW 
        incorrectes++;
      }

       if (c!='\0'){//Affiche score
       totale++;
        printLcd (2,1,String (correctes)+":"+String (incorrectes)+"  ");
        if (totale>=MAX_JEU ){//A atteint le nombre maximal de lettres ?
          if ((correctes*100/totale)>=50){
            printLcd (0,1,"VOUS AVEZ GAGNE!");
            playMarioVictoryMelody();//Winner
          }else{
            printLcd (0,1,"VOUS AVEZ PERDU ");
            playMarioGameOverMelody();//Game over Mario
          }
                     //0123456789ABCDEF  
          printLcd (0,1,"NEW GAME ENTER  ");

          cw.clearBuffer();
          while (!cw.isBuffer()){Usb.Task();delay(500);}//WAIT FOR new game
          cw.clearBuffer();//Elimine ENTER

          printLcd (0,1,"                 ");
          printLcd (2,1,String (correctes)+":"+String (incorrectes)+"  ");
          //Reset
          nouvelle =true;//nouvelle lettre aleatoire
          totale=0;
          correctes=0;
          incorrectes=0;
    
        }
      }  
    }

  
}
