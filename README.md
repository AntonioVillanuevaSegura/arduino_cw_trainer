Arduino CW trainer

LiquidCrystal_I2C lcd(0x27,cols ,lignes);  // Address i2c 0x27 0x3f

USB Usb;
HIDBoot<USB_HID_PROTOCOL_KEYBOARD> HidKeyboard(&Usb);
CW cw;

TOUCHE SHIFT+ 
1-2 VITESSE 
3-4 FREQUENCE
5- LETTRES
6  NOMBRES 
