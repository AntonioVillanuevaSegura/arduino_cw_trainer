#ifndef CW_H
#define CW_H
#include <Arduino.h>

#include "ecran.h"
#include "keyboard.h"

#define MAX_JEU 10 //Nombre maximal de lettres par jeu  ou constexpr int MAX = 10; c++11 !!
extern bool nouvelle;
extern char lettre;
extern char c;
extern int totale;
extern int correctes;
extern int incorrectes;

// Definición de las notas musicales (frecuencias en Hz)
#define NOTE_C4 261.63
#define NOTE_D4 293.66
#define NOTE_E4 329.63
#define NOTE_F4 349.23
#define NOTE_G4 391.99
#define NOTE_A4 440.00
#define NOTE_B4 493.88
#define NOTE_C5 523.25
#define NOTE_D5 587.33
#define NOTE_E5 659.25
#define NOTE_F5 698.46
#define NOTE_G5 783.99
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
#define SIXTEENTH_NOTE 62 // Semicorchea

// Duraciones de las notas (en milisegundos)
#define WHOLE_NOTE 1000   // Nota entera
#define HALF_NOTE 500     // Media nota
#define QUARTER_NOTE 250  // Negra
#define EIGHTH_NOTE 125   // Corchea
#define SIXTEENTH_NOTE 62 // semicorchea

#define SALIDA 3 //D3 arduino UNO

//Creamos un diccionario KEY:VALUE donde cada signo  tiene su correspondencia CW
extern const char* key1[];
extern const char* value1[];

void setUpCw(unsigned int p, int f);
String getCwCode(char caracter);
void playCW (String cw);
unsigned int calcularTimingCW(int wpm);
const char* letreAleatorie(int intervale = 26) ;
void erreurTone();
void playMarioVictoryMelody();
void playMarioGameOverMelody();
void jeuCW1 (CW& cw,int& mpm, int& freq, int& menu);
#endif