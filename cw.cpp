#include "cw.h"

bool nouvelle = true;
char lettre='/0' ;
char c='/0';

int totale=0;
int correctes=0;
int incorrectes=0;

unsigned int point = 167;//calcularTimingCW(mpm)
int frecuencia =700; //Frecuencia CW 

const char* key1[] = {
  "A", "B", "C", "D", "E", "F", "G", "H", "I", "J",
  "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T",
  "U", "V", "W", "X", "Y", "Z",
  "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", " "
};

const char* value1[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
  "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
  "..-", "...-", ".--", "-..-", "-.--", "--..",
  "-----", ".----", "..---", "...--", "....-", ".....", 
  "-....", "--...", "---..", "----.", "-----",
  " "
};

void setUpCw(unsigned int p, int f){
	point=calcularTimingCW(p);
	frecuencia=f;

}
// obtient le code CW d'un signe, par exemple A renvoie .-
String getCwCode(char caracter) { 
	Serial.print (caracter);//Debug caracter
	if (caracter==' '){return " ";}//Retorna espacio 

	//Recorre la matriz de key creando indices 
	for (int index=0;index<(sizeof(key1)/sizeof(key1[0]));index++){//Recorre key
		
		if ( key1[index][0] ==  toupper(caracter) ){
			return value1[index];
		}
	}
	return "";
}

//Joue le son CW à partir du symbole
void playCW (String cw){
	Serial.print("(" +cw+ ") ");
	//Parcour l'équivalent CW, les points, les tirets et les espaces de CW.

	for (int index=0;index<cw.length();index++){
		
		if (cw.charAt(index) =='.'){tone(AUDIO, frecuencia);delay(point); noTone(AUDIO); delay(point );}//point.
		else if (cw.charAt(index) =='-'){tone(AUDIO, frecuencia);delay(point * 3); noTone(AUDIO); delay(point );}//tiret
		else { delay(point); }//Espace entre les éléments point & tirets		
	
	}
	delay (point*3);
}

//Calcula el tiempo de un point en funcion de los WPM seleccionados
unsigned int calcularTimingCW(int wpm) {
  return (unsigned int)(1320.0 / wpm);
}

//Retourne une lettre aleatorie
const char* letreAleatorie(int intervale = 26) { //26 lettres o 36 lettres + nombres

	return key1[ random(0, intervale) ];

}

//ton d'erreur quand on fait une erreur
void erreurTone(){
	tone(AUDIO, 100);delay(1000); noTone(AUDIO);
}

//La mélodie de Mario Bros quand on a gagné
void playMarioVictoryMelody() {
  int melody[] = {
    NOTE_E4, NOTE_G4, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_G4
  };

  int durations[] = {
    QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE,
    QUARTER_NOTE, QUARTER_NOTE, HALF_NOTE
  };

  for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
    tone(AUDIO, melody[i], durations[i]);
    delay(durations[i] * 1.3);
    noTone(AUDIO);
  }
}

//La mélodie de Mario Bros quand on perd
void playMarioGameOverMelody() {
  // Notas para la melodía de "Game Over" de Mario
  int melody[] = {
    NOTE_E5, NOTE_G4, NOTE_E4, NOTE_C5, NOTE_D4, NOTE_G4
  };

  // Duraciones de las notas (en milisegundos)
  int durations[] = {
    QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE,
    QUARTER_NOTE, QUARTER_NOTE, HALF_NOTE + QUARTER_NOTE
  };

  // Reproducir la melodía
  for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
    tone(AUDIO, melody[i], durations[i]);
    delay(durations[i] * 1.3); // Pausa entre notas
    noTone(AUDIO);
  }
}

//Fonction qui définit le jeu classique
void jeuCW1 (KeyboardUSB& cw,int& mpm, int& freq, int& menu){

  //Lettre Aleatoire obtien le code CW  getCwCode et playCW
  //Génère une lettre aléatoire que nous devons devine et Émets le CW
  if (nouvelle){
		//Lecture d'une lettre aleatoire 
   if (menu==1) {lettre=*letreAleatorie(36);}//lettres + nombres
	 else {lettre=*letreAleatorie(26);}//lettres
   playCW  (getCwCode(lettre));
  
   printLcd (9,1,String (lettre)+"  ");//DEBUG random
   nouvelle=false;
   printLcd (10,1,"      ");
   totale++;//une nouvelle lettre
    
  }

    if (cw.isBuffer()){//Une touche a été appuyée ?
    
      printLcd (9,1,"        ");

      c=cw.getBuffer()[0];//Get touche
      cw.clearBuffer();

      if (c==0x28){c='\0';}//ENTER

      //MPM MENU FREQ
      if (c=='&'){mpm++;c = '\0'; setUpCw(mpm, freq);} //1 &
      if (c==126){mpm--;c = '\0'; setUpCw(mpm, freq);} //2 ~

      if (c==35){menu++;c = '\0';} //3 #
      if (c==123){menu--;c = '\0';} //4 {  

      if (menu<0 ){menu=0;}
      if (menu>1 ){menu=1;}

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
        //printLcd (10,1,"NON !");
        printLcd (10,1,String(c)+" ");
        erreurTone();
        printLcd (10,1,"      ");

       // playCW  (getCwCode(lettre));//Erreur rePlay CW 
        incorrectes++;       
        nouvelle =true;//nouvelle lettre aleatoire
      }

       if (c!='\0'){//Il s'agit d'une touche d'entrée pour le jeu
        printLcd (2,1,String (correctes)+":"+String (incorrectes)+"  ");

        if (totale>=MAX_JEU ){//A atteint le nombre maximal de lettres ?
          if ((correctes*100.0/totale)>=70){
            printLcd (0,1,"VOUS AVEZ GAGNE!");
            playMarioVictoryMelody();//Winner
          }else{
            printLcd (0,1,"VOUS AVEZ PERDU ");
            playMarioGameOverMelody();//Game over Mario
          }
 
          printLcd (0,1,"NEW GAME ENTER  ");

          cw.clearBuffer();
          while (!cw.isBuffer()){Usb.Task();delay(500);}//Attends une touche pour démarrer une nouvelle partie
          cw.clearBuffer();//Elimine touche ...ENTER dans le buffer

          printLcd (0,1,"                 ");
          printLcd (2,1,String (correctes)+":"+String (incorrectes)+"  ");
          //Reset .Efface les variables d'une nouvelle partie
          nouvelle =true;//nouvelle lettre aleatoire
          totale=0;
          correctes=0;
          incorrectes=0;
    
        }
      }  
    }
}


