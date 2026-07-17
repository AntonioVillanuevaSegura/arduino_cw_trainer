#include "cw.h"

unsigned int punto = 167;//calcularTimingCW(mpm)
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
	punto=calcularTimingCW(p);
	frecuencia=f;

}
// obtiene el codigo CW de un signo , p.e A retorna .-
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

//Play sonido CW ,del simbolo 
void playCW (String cw){
	Serial.print("(" +cw+ ") ");
	//Recorre el equivalente CW , puntos , rayas y espacios del CW

	for (int index=0;index<cw.length();index++){
		
		if (cw.charAt(index) =='.'){tone(SALIDA, frecuencia);delay(punto); noTone(SALIDA); delay(punto );}//punto .
		else if (cw.charAt(index) =='-'){tone(SALIDA, frecuencia);delay(punto * 3); noTone(SALIDA); delay(punto );}//raya _
		else { delay(punto); }//Espacio	entre elementos punto raya
		//delay( (punto * 2) );			
	
	}
	delay (punto*3);


	/*
	for (int index=0;index<cw.length();index++){
		
		if (cw.charAt(index) =='.'){tone(SALIDA, frecuencia);delay(punto); noTone(SALIDA); delay(punto * 3);}//punto .
		else if (cw.charAt(index) =='-'){tone(SALIDA, frecuencia);delay(punto * 3); noTone(SALIDA); delay(punto / 2);}//raya _
		else { delay(punto); }//Espacio	entre elementos punto raya
		delay( (punto * 2) );			
	
	}
	delay (punto*2);
	*/
}

//Calcula el tiempo de un punto en funcion de los WPM seleccionados
unsigned int calcularTimingCW(int wpm) {
  return (unsigned int)(1320.0 / wpm);
}

//Retourne une lettre aleatorie
//const char* letreAleatorie(int intervale = 26) { //26 lettres o 36 lettres + nombres
const char* letreAleatorie(int intervale = 26) { //26 lettres o 36 lettres + nombres

	return key1[ random(0, intervale) ];

}


void erreurTone(){
	tone(SALIDA, 100);delay(300); noTone(SALIDA);
}

// Notas musicales (frecuencias en Hz)
#define NOTE_E4 329.63   // Mi de la 4ª octava (E4)
#define NOTE_G4 391.99   // Sol de la 4ª octava (G4)
#define NOTE_E5 659.25   // Mi de la 5ª octava (E5)
#define NOTE_C5 523.25   // Do de la 5ª octava (C5)
#define NOTE_D5 587.33   // Re de la 5ª octava (D5)
#define NOTE_G5 783.99   // Sol de la 5ª octava (G5)

// Duraciones de las notas (en milisegundos)
#define WHOLE_NOTE 1000   // Nota entera
#define HALF_NOTE 500     // Media nota
#define QUARTER_NOTE 250  // Negra
#define EIGHTH_NOTE 125   // Corchea
#define SIXTEENTH_NOTE 62 // semicorchea


void playMarioVictoryMelody() {
  int melody[] = {
    NOTE_E4, NOTE_G4, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_G4
  };

  int durations[] = {
    QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE,
    QUARTER_NOTE, QUARTER_NOTE, HALF_NOTE
  };

  for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
    tone(SALIDA, melody[i], durations[i]);
    delay(durations[i] * 1.3);
    noTone(SALIDA);
  }
}
