#include "keyboard.h"

USB Usb;
HIDBoot<USB_HID_PROTOCOL_KEYBOARD> HidKeyboard(&Usb);
CW cw;

    void CW::OnKeyDown(uint8_t mod, uint8_t key) {
      Serial.print("DN ");
      uint8_t c = OemToAscii(mod, key);
      if (c) OnKeyPressed(c);
    }

    void CW::OnKeyUp(uint8_t mod, uint8_t key) {
      Serial.print("UP ");
    }

    void CW::OnKeyPressed(uint8_t key) {
      char c=toupper ((char)key);
      conversionAzerty( &c);
      if (bufferIndex < sizeof(buffer) - 1) {
        buffer[bufferIndex++] = c;
        buffer[bufferIndex] = '\0';  // Terminar string
      }

  
    }

    bool CW::isBufferFull() {return bufferIndex >= sizeof(buffer) - 1;}
    bool CW::isBuffer() {return bufferIndex >0;}   
    char* CW::getBuffer() { return buffer; }
    void CW::clearBuffer() {
      bufferIndex = 0;
      memset(buffer, 0, sizeof(buffer));
    } 

    void CW::conversionAzerty(char *c){
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


