#ifndef CW_H
#define CW_H
#include <Arduino.h>
/*
unsigned int punto = 167;//calcularTimingCW(mpm)
int frecuencia =700; //Frecuencia CW 
*/
#define SALIDA 6 //6->D3 arduino NANO

//Creamos un diccionario KEY:VALUE donde cada signo  tiene su correspondencia CW
extern const char* key1[];
extern const char* value1[];
/*
extern const char* key1[] = {
  "A", "B", "C", "D", "E", "F", "G", "H", "I", "J",
  "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T",
  "U", "V", "W", "X", "Y", "Z",
  "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", " "
};

extern const char* value1[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
  "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
  "..-", "...-", ".--", "-..-", "-.--", "--..",
  "-----", ".----", "..---", "...--", "....-", ".....", 
  "-....", "--...", "---..", "----.", "-----",
  " "
};
*/
String getCwCode(char caracter);
void playCW (String cw);
unsigned int calcularTimingCW(int wpm);
const char* letreAleatorie(int intervale = 26) ;
#endif