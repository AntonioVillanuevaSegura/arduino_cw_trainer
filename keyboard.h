//Gestion d'un clavier USB dans Arduino Hôte USB 
//https://www.amazon.fr/dp/B0C8TNZ1QQ?ref=ppx_yo2ov_dt_b_fed_asin_title
#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <ctype.h> //toupper(c)
//https://github.com/arduino-libraries/USBHost/blob/master/src/hidboot.h
#include <hidboot.h>
#include <usbhub.h>
#include <SPI.h>

#include "ecran.h"

class KeyboardUSB: public KeyboardReportParser {
  protected:
    void OnKeyDown(uint8_t mod, uint8_t key);
    void OnKeyUp(uint8_t mod, uint8_t key);
    void OnKeyPressed(uint8_t key);
  public:

    bool isBufferFull() ;
    bool isBuffer() ;   
    char* getBuffer();
    void clearBuffer() ;
    void debugKeyboard();  
    void printSetup(int mpm,int freq,int menu, int correctes,int incorrectes);
  
  private:  
    void KeyboardUSB::conversionAzerty(char *c);
    char c;//Simple char
    char buffer[32];      // Buffer para acumular teclas
    int bufferIndex;      // Índice del buffer 
    const String menuOption[5] = {"1 LETRES", "2 LETRES+NOMBRES", "3 NOMBRES","4 VITESSE","5 FREQ"}; 
    uint8_t i;//index menu
};


extern USB Usb;
extern HIDBoot<USB_HID_PROTOCOL_KEYBOARD> HidKeyboard;
extern KeyboardUSB keyboard_usb;

#endif