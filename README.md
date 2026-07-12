Arduino CW trainer

LiquidCrystal_I2C lcd(0x27,cols ,lignes);  // Address i2c 0x27 0x3f

USB Usb;
HIDBoot<USB_HID_PROTOCOL_KEYBOARD> HidKeyboard(&Usb);
CW cw;

MENU 
1 vitesse MPM
2 LETRES
3 LETRES+NOMBRES
