#include "keyboard.h"

USB Usb;
HIDBoot<USB_HID_PROTOCOL_KEYBOARD> HidKeyboard(&Usb);
KeyboardUSB keyboard_usb;

    void KeyboardUSB::OnKeyDown(uint8_t mod, uint8_t key) {
      Serial.print("DN ");
      uint8_t c = OemToAscii(mod, key);
      if (c) OnKeyPressed(c);
    }

    void KeyboardUSB::OnKeyUp(uint8_t mod, uint8_t key) {
      Serial.print("UP ");
    }

    void KeyboardUSB::OnKeyPressed(uint8_t key) {
      char c=toupper ((char)key);
      conversionAzerty( &c);
      if (bufferIndex < sizeof(buffer) - 1) {
        buffer[bufferIndex++] = c;
        buffer[bufferIndex] = '\0';  // Terminar string
      }

  
    }

    bool KeyboardUSB::isBufferFull() {return bufferIndex >= sizeof(buffer) - 1;}
    bool KeyboardUSB::isBuffer() {return bufferIndex >0;}   
    char* KeyboardUSB::getBuffer() { return buffer; }
    void KeyboardUSB::clearBuffer() {
      bufferIndex = 0;
      memset(buffer, 0, sizeof(buffer));
    } 

    void KeyboardUSB::conversionAzerty(char *c){
      //Fonction pour adapter à un clavier français
      if (*c=='Q'){*c='A';return; }
      if (*c=='A'){*c= 'Q';return;}

      if (*c=='Z'){*c= 'W';return;}
      if (*c=='W'){*c= 'Z';return;}
      
      if (*c==';'){*c='M';return; }
      if (*c=='M'){*c=',';return; }  

      //Shift + touche
      if (*c=='!'){*c='&';return; }
      if (*c=='@'){*c='~';return;} 
      if (*c=='!'){*c='&';return; }  
      if (*c=='$'){*c='{';return; }  
      if (*c=='%'){*c='(';return; }  
      if (*c=='!'){*c='&';return; }
      if (*c=='^'){*c='-';return; } 
      if (*c=='&'){*c='`';return; }  
      if (*c=='*'){*c=0x7C;return;}   
      if (*c=='('){*c='^';return; }  
      if (*c==')'){*c='@';return; } 
      if (*c=='{'){*c='^';return; }       

    }    

    void KeyboardUSB::debugKeyboard(){
      if (KeyboardUSB::isBuffer()){
        char c =KeyboardUSB::getBuffer()[0];
        KeyboardUSB::clearBuffer();
        printLcd (0,0,String (c));
        printLcd(0, 1, String((unsigned char) (c )));
        Serial.println((unsigned char) (c ));
   
      }
    }

    void KeyboardUSB::printSetup(int mpm,int freq,int menu, int correctes,int incorrectes){
      printLcd (0,0,"MPM:" +String(mpm)+"   ");
      printLcd (7,0,"F"+String(freq)+"   ");
      printLcd (12,0,"M:"+String(menu)+"   ");
      printLcd (2,1,String (correctes)+":"+String (incorrectes)+"  ");

    }

