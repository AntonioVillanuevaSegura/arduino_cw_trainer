#include "cw.h"
#include <Arduino.h>

// obtiene el codigo CW de un signo , p.e A retorna .-
String getCwCode(char caracter) { 
	Serial.print (caracter);//Debug caracter
	if (caracter==' '){return " ";}//Retorna espacio 

	//Recorre la matriz de key creando indices 
	for (int index=0;index<(sizeof(key)/sizeof(key[0]));index++){//Recorre key
		
		if ( key[index][0] ==  toupper(caracter) ){
			return value[index];
		}
	}
	return "";
}

//Play sonido CW ,del simbolo 
void playCW (String cw){
	Serial.print("(" +cw+ ") ");
	//Recorre el equivalente CW , puntos , rayas y espacios del CW
	for (int index=0;index<cw.length();index++){
		
		if (cw.charAt(index) =='.'){tone(SALIDA, frecuencia);delay(punto); noTone(SALIDA); delay(punto * 3);}//punto .
		else if (cw.charAt(index) =='-'){tone(SALIDA, frecuencia);delay(punto * 3); noTone(SALIDA); delay(punto / 2);}//raya _
		else { delay(punto); }//Espacio	entre elementos punto raya
		delay( (punto * 2) );			
	
	}
	delay (punto*2);
}

//Calcula el tiempo de un punto en funcion de los WPM seleccionados
unsigned int calcularTimingCW(int wpm) {
  return (unsigned int)(1320.0 / wpm);
}
