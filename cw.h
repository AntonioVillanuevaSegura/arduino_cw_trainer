#ifndef CW_H
#define CW_H
#include <Arduino.h>

#include "ecran.h"
#include "keyboard.h"

#define AUDIO 3 //D3 arduino UNO , sortie audio
#define MAX_JEU 10 //Nombre maximal de lettres par jeu  ou constexpr int MAX = 10; c++11 !!
extern bool nouvelle;
extern char lettre;
extern char c;
extern int totale;
extern int correctes;
extern int incorrectes;

// Définition des notes de musique (fréquences en Hz) Mario Bros
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

// Durée des notes (en millisecondes) Mario Bros
#define WHOLE_NOTE 1000 
#define HALF_NOTE 500
#define QUARTER_NOTE 250
#define EIGHTH_NOTE 125 
#define SIXTEENTH_NOTE 62 

//On créé un dictionnaire CLÉ:VALEUR où chaque symbole a sa correspondance CW.
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