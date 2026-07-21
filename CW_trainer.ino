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

  //Lettre Aleatoire obtien le code CW  getCwCode et playCW
  //Génère une lettre aléatoire que nous devons devine et Émets le CW
  if (nouvelle){
   lettre=*letreAleatorie(26);//Lecture d'une lettre aleatoire 
   playCW  (getCwCode(lettre));
  
   printLcd (9,1,String (lettre)+"  ");//DEBUG random
   nouvelle=false;
   printLcd (10,1,"      ");
   totale++;//une nouvelle lettre
    
  }

  //while (!cw.isBuffer()){Usb.Task();}

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

        //printLcd (10,1,"NON ="+c);
        printLcd (10,1,"NON !");
        erreurTone();
        printLcd (10,1,"      ");

        playCW  (getCwCode(lettre));//Erreur rePlay CW 
        incorrectes++;
       
        nouvelle =true;//nouvelle lettre aleatoire

      }

       if (c!='\0'){//Il s'agit d'une touche d'entrée pour le jeu
        printLcd (2,1,String (correctes)+":"+String (incorrectes)+"  ");

        if (totale>=MAX_JEU ){//A atteint le nombre maximal de lettres ?
          if ((correctes*100.0/totale)>=90){
            printLcd (0,1,"VOUS AVEZ GAGNE!");
            playMarioVictoryMelody();//Winner
          }else{
            printLcd (0,1,"VOUS AVEZ PERDU ");
            playMarioGameOverMelody();//Game over Mario
          }
 
          printLcd (0,1,"NEW GAME ENTER  ");

          cw.clearBuffer();
          while (!cw.isBuffer()){Usb.Task();delay(500);}//Attends une touche pour démarrer une nouvelle partie
          cw.clearBuffer();//Elimine ENTER dans le buffer

          printLcd (0,1,"                 ");
          printLcd (2,1,String (correctes)+":"+String (incorrectes)+"  ");
          //Reset .Effacer les variables d'une nouvelle partie
          nouvelle =true;//nouvelle lettre aleatoire
          totale=0;
          correctes=0;
          incorrectes=0;
    
        }
      }  
    }

  
}
