#include <ctype.h> //toupper(c)
//https://github.com/arduino-libraries/USBHost/blob/master/src/hidboot.h
#include <hidboot.h>
#include <usbhub.h>
#include <SPI.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Broche 18 - A4 - SDA Broche 19 - A5 - SCL
//LCD 1602A I2C https://docs.arduino.cc/libraries/liquidcrystal-i2c/
#define cols 16
#define lignes 2

LiquidCrystal_I2C lcd(0x27,cols ,lignes);  // Address i2c 0x27 0x3f


USB Usb;
HIDBoot<USB_HID_PROTOCOL_KEYBOARD> HidKeyboard(&Usb);


class CW: public KeyboardReportParser {
  protected:
    void OnKeyDown(uint8_t mod, uint8_t key);
    void OnKeyUp(uint8_t mod, uint8_t key);
    void OnKeyPressed(uint8_t key);
  public:
    void displayMenu();
    bool isBufferFull() ;
    bool isBuffer() ;   
    char* getBuffer();
    void clearBuffer() ;
  
  private:
    void printCharLCD(char &c,int x,int y);
    //void printStringLCD(int x,int y,const char* s);
    void printStringLCD(const String &s,int x,int y);    
    void CW::conversionAzerty(char *c);
    char c;//Simple char
    char buffer[32];      // Buffer para acumular teclas
    int bufferIndex;      // Índice del buffer 
    const String menuOption[5] = {"1 LETRES", "2 LETRES+NOMBRES", "3 NOMBRES","4 VITESSE","5 FREQ"}; 
    uint8_t i;//index menu
};

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
      /*
      Serial.println(c);
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print (c);
      */
      if (bufferIndex < sizeof(buffer) - 1) {
        buffer[bufferIndex++] = c;
        buffer[bufferIndex] = '\0';  // Terminar string
      }

  
}
    
    void CW::displayMenu(){
      char c=0x00;
      if (isBuffer()){
        c=getBuffer()[0];
        //printStringLCD( ,0  ,0);
      }

      switch(c){
        case '+':++i;break;
        case '-':--i;break;
        case 0x28:++i;break;
        default:
          break;

      }
  
        if (i>=5  ) {i=0;}   
        printStringLCD( menuOption[i],0  ,1);
        clearBuffer();
        delay(500);      



    }

    bool CW::isBufferFull() {return bufferIndex >= sizeof(buffer) - 1;}
    bool CW::isBuffer() {return bufferIndex >= 0;}   
    char* CW::getBuffer() { return buffer; }
    void CW::clearBuffer() {
      bufferIndex = 0;
      memset(buffer, 0, sizeof(buffer));
    } 
    void CW::printCharLCD(char &c,int x,int y){
      lcd.clear();
      lcd.setCursor(x, y);
      lcd.print (c);      
    }


    void CW::printStringLCD(const String &s,int x,int y){
      lcd.clear();
      lcd.setCursor(x, y);      
      lcd.print(s);
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

CW Prs;

void setup() {
  //Ecran
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("F4LEC");
  
  Serial.begin(115200);
  Serial.println("Start");
  if (Usb.Init() == -1)
    Serial.println("KEYBOARD problem.");
  delay(200);
  HidKeyboard.SetReportParser(0, &Prs);
}

void loop() {  
  Usb.Task();
  lcd.setCursor(0, 0);
  lcd.print("F4LEC");  
  /*
  if (Prs.isBuffer()){
          //lcd.clear();
      lcd.setCursor(0,1);      
      lcd.printstr(Prs.getBuffer());
      Prs.clearBuffer();
      
  }
  */
  Prs.displayMenu();
  
}
